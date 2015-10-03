#include "kernel.h"
#include "ctrdrv.h"

#define POOLSIZE        10
#define NUMBER_OF_TASKS (POOLSIZE - 1)

/* Put the idle task on last position */
#define IDLE_PROC_ID    (POOLSIZE - 1)
#define MIN_INT         -30000

#define STACK_SIZE       400

static char task_stack[STACK_SIZE]; 

static volatile uint32_t SPAtual;

/* Last position available in the stack */
volatile static uint32_t SP;

volatile static uint32_t sp_tmp;
ptrFunc p_fcn;

/* Variáveis do kernel */
volatile process pool[POOLSIZE];
volatile uint8_t actualTask;
volatile uint8_t lastTask;

/* Variable to define the actual task on round robin scheduler */
volatile int8_t RRactualTask;

/* This is the Idle process, 
 * the only process on kernel that is banked
 */
void IdleFunc(void) {
        /* Start interval timer */
        R_IT_Start();

        /* Enable interrupts */ 
        asm("ei");

        for(;;) {
                /* energy saving here */
        }
}

void timedLoopStart(signed int valor)
{
        pool[actualTask].Time = valor;
}

void timedLoopWait(void)
{
        pool[actualTask].Status = WAITING;
        while (pool[actualTask].Status == WAITING);
}

void delay(signed int valor)
{
        timedLoopStart(valor);
        timedLoopWait();
}

void createStack(ptrFunc func, uint32_t position)
{
        /*
         * General purpose registers:
         * AX, BC, DE, HL   (16 bits)
         *
         * Special purpose registers:
         * PSW    (8 bits)
         * PC     (20 bits)
         * SP     (16 bits)
         * ES     (8 bits)
         * CS     (8 bits)
         * PMC    (8 bits)
         */

        /* Initial PSW value allocated to a newly created task.
         *   11000110 = 0xC6
         *   ||||||||-------------- Carry flag (reset)
         *   |||||||--------------- In-service priority 0 flag (reset)
         *   |||||----------------- In-service priority 1 flag (reset) 
         *   ||||------------------ Register bank select 0 flag (reset) 
         *   |||------------------- Auxiliary carry flag cleared (reset)
         *   ||-------------------- Register bank select 1 flag (reset)
         *   |--------------------- Zero flag (set)
         *   ---------------------- Global interrupt enable flag (set)
         */
        sp_tmp = position;
        p_fcn = func;

        asm("push   ax");
        asm("push   bc");
        asm("push   hl");

        /* Store SP and set new temporary SP */
        asm("movw   bc, sp");
        asm("movw   ax, #_sp_tmp");
        asm("movw   hl, ax");
        asm("movw   ax, [hl]");
        asm("movw   sp, ax");

        /* Pushing PSW to SP-1 */
        asm("movw   ax, #0C600h");
        asm("push   ax");

        /* Pushing PC to SP */
        asm("movw   ax, #_p_fcn");
        asm("movw   hl, ax");
        asm("movw   ax, [hl]");
        asm("push   ax");

        /* Pushing AX to SP */
        asm("movw   ax, #0aaaah");
        asm("push   ax");

	/* Pushing HL to SP */
        asm("movw   ax, #0ffffh");
        asm("push   ax");

	/* Pushing ES and CS to SP */
        asm("movw   ax, #00f00h");
        asm("push   ax");

	/* Pushing DE to SP */
        asm("movw   ax, #0dedeh");
        asm("push   ax");

	/* Pushing BC to SP */
        asm("movw   ax, #0bcbch");
        asm("push   ax");

        /* Restore SP */
        asm("movw   ax, bc");
        asm("movw   sp, ax");

        asm("pop    hl");
        asm("pop    bc");
        asm("pop    ax");
}

void CreateIdleProc(void)
{
        /* Idle process creation */
        pool[IDLE_PROC_ID].StackInit = SP;
        pool[IDLE_PROC_ID].Status = READY;
        pool[IDLE_PROC_ID].Function = IdleFunc;

        /*  
         *  Pushing function address into the stack
         *  (most significant byte first)
         *
         *  The function address is 20 bits, 
         *  which means it will occupy 4 positions of
         *  1 byte in the stack:
         *
         *  SP    ->   
         *  SP-1  ->  0x00
         *  SP-2  ->  PC19-PC16
         *  SP-3  ->  PC15-PC8
         *  SP-4  ->  PC7-PC0
         */
        p_fcn = IdleFunc;

        /* Storing registers */
        asm("push   ax");
        asm("push   bc");
        asm("push   hl");
        asm("push   de");

        /* Storing and updating SP register */
        asm("movw   bc, sp");
        asm("movw   ax, #_SP");
        asm("movw   hl, ax");
        asm("movw   ax, [hl]");
        asm("movw   sp, ax");

        /* Pushing PSW and PC */
        asm("movw   ax, #0C600h");
        asm("push   ax");
        asm("movw   ax, #_p_fcn");
        asm("movw   hl, ax");
        asm("movw   ax, [hl]");
        asm("push   ax");

        /* Restore SP */
        asm("movw   ax, bc");
        asm("movw   sp, ax");

        /* Restoring registers */
        asm("pop    de");
        asm("pop    hl");
        asm("pop    bc");
        asm("pop    ax");

        SP -= 4;

        /* Stack end point */
        pool[IDLE_PROC_ID].StackPoint = SP;
        /* Jump to the next "stack slot" */
        SP = pool[IDLE_PROC_ID].StackInit - 50;
}

int8_t kernelInit(void) 
{
        unsigned char i;

        /* Starting all positions as empty */
        for (i = 0; i < NUMBER_OF_TASKS; i++){
                pool[i].Status = EMPTYSLOT;
        }

        lastTask = 0;

        /* Pointing SP to the bottom of stack */
        SP = 0xf0000;
        SP |= ((uint16_t) (task_stack + STACK_SIZE));

        CreateIdleProc();

        actualTask = IDLE_PROC_ID;
        RRactualTask = 0;

        return SUCESSO;
}

int8_t kernelAddProc(ptrFunc func, int stkSize, priorityMode newPrio)
{
        /* lastTask is a pointer to the next free space in the pool */
        if (lastTask == NUMBER_OF_TASKS) {
                return FALHA;
        }

        pool[lastTask].StackInit = SP;
        pool[lastTask].prioridade = newPrio;
        pool[lastTask].Status = READY;
        pool[lastTask].Function = func;

        /* Give a little time to all processes to avoid RTOS false warning */
        pool[lastTask].Time = 10; 

        createStack(func, SP);

        /* Stack end point */
        pool[lastTask].StackPoint = SP - 14;

        /* Jump to the next stack free position */
        SP -= stkSize;

        /* Point to next free space */
        lastTask++;

        return SUCESSO;
}

uint32_t SP_dummy;

void kernelLoop(void) 
{
        pool[IDLE_PROC_ID].Status = RUNNING;
        SP_dummy = pool[IDLE_PROC_ID].StackPoint;
        actualTask = IDLE_PROC_ID;

        /* Restore SP */
        asm("movw   ax, #_SP_dummy");
        asm("movw   hl, ax");
        asm("movw   ax, [hl]");
        asm("movw   sp, ax");

        /* Load of context is done by reti */
        asm("reti");

        /* Should not get here */
        for (;;);
}

int8_t Scheduler(void)
{
        char i;
        char next = IDLE_PROC_ID;

        if (lastTask == 0) {
                return next;
        }

        /* Update tick count for each process except the one running */
        for (i = 0; i < lastTask; i++){
                if (pool[i].Status != EMPTYSLOT){
                        if (pool[i].Time > -30000){
                                pool[i].Time--;
                        }
                        if (pool[i].Time <= 0){
                                pool[i].Status = READY;
                        }
                }
        }

        /* RTOS priority check */
        for (i = 0; i < lastTask; i++){
                if((pool[i].prioridade == RTOS) &&
                   (pool[i].Status == READY)) {
                        return i;
                }
        }

        /* RRS: round-robin scheduler
         * Start from the next task and go all the way around  
         */
        i = (RRactualTask+1);
        if (i>=lastTask) {
                i = 0;
        }
        while ((i != RRactualTask) && 
               (pool[i].Status != READY)) {
                i++;
                if (i >= lastTask) {
                        i = 0;
                }
        }

        /* If the variable "i" comes back to nextTask
         * there aren't any other task willing to run
         */
        if ((i == RRactualTask) && 
            (pool[i].Status == WAITING)) {
                return IDLE_PROC_ID;
        } else {
                RRactualTask=i;
                next = i;
        }

        /* In the end, 'next' has the next task for both scheduler algorithms */
        if (next >= lastTask) {
                return IDLE_PROC_ID;
        }
        return next;
}

/* This function is called every IT interrupt */
void kernelClock(void)
{
        /* Store AX */
        asm("movw   r10, ax");

        /* Remove stack pushes added by the compiler  
         * INT_IT      -> 18     bytes
         * kernelClock -> 4 + 4  bytes 
         */
        asm("movw   ax, sp");
        asm("addw   ax, #26");
        asm("movw   sp, ax");
       
        /* Restore AX */
        asm("movw   ax, r10");

        /* Save process context */
        asm("push   ax");
        asm("push   hl");
        asm("mov    a, cs");
        asm("xch    a, x");
        asm("mov    a, es");
        asm("push   ax");
        asm("push   de");
        asm("push   bc");

        /* Save SP into SPAtual */
        asm("movw   ax, #_SPAtual");
        asm("movw   hl, ax");
        asm("movw   ax, sp");
        asm("movw   [hl], ax");

        pool[actualTask].StackPoint = SPAtual;

        /* Get next task */
        actualTask = Scheduler();

        SPAtual = pool[actualTask].StackPoint;

        /* Clear IT interrupt flag */
        ITIF = 0u;

        /* Load new process */
        asm("movw   ax, #_SPAtual");
        asm("movw   hl, ax");
        asm("movw   ax, [hl]");
        asm("movw   sp, ax");
        asm("pop    bc");
        asm("pop    de");
        asm("pop    ax");
        asm("mov    es, a");
        asm("xch    a, x");
        asm("mov    cs, a");
        asm("pop    hl");
        asm("pop    ax");

        asm("reti");
}
