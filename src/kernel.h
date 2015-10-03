#ifndef _KERNEL_H
#define _KERNEL_H

#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"

typedef enum{
	EMPTYSLOT, 
        RUNNING, 
        READY, 
        WAITING
} processState;

typedef enum{
	NORMAL, 
        RTOS
} priorityMode;

/*  define um ponteiro de função  */
typedef void (*ptrFunc)(void);

typedef struct {
        ptrFunc Function;
        volatile int16_t Time;
        /*  Actual process state  */
        volatile processState Status;
        volatile priorityMode prioridade;
        volatile uint32_t StackPoint;
        /*  Virtual stack pointer init  */
        volatile uint32_t StackInit;
} process;

int8_t kernelInit(void);
int8_t kernelAddProc(ptrFunc func, int stkSize, priorityMode newPrio);
void kernelLoop(void);
void kernelClock(void);

#endif
