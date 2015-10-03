#include "kernel.h"
#include "ctrdrv.h"

#define PRECISAO 3
#define COMMAND_MAX_SIZE 10

uint8_t count_stop = 1;
uint8_t count_reset = 0;
int16_t count_relogio = 0;

char procRelogio(void)
{
        uint8_t lcd_digito[5] = {0, 0, ':', 0, 0};
        for (;;) {
                timedLoopStart(PRECISAO);
                /* Relógio envia os 4 dígitos a serem mostrados. Ex: 1230 (12:30) */
                if (count_stop == 0 && count_reset == 0) {
                        /* Variável deve ser multiplicada pelo número de processos */
                        count_relogio += PRECISAO;
                        if (count_relogio >= 6000)
                                count_relogio = 0;
                }
                lcd_digito[0] = (count_relogio / 1000) % 10;
                lcd_digito[1] = (count_relogio / 100) % 10;
                lcd_digito[3] = (count_relogio / 10) % 10;
                lcd_digito[4] = count_relogio % 10;
                callDriver(DRV_LCD, LCD_SECB, (void *) lcd_digito);
                timedLoopWait();
        }
}

char teclado(void)
{
	uint8_t tecla;

        for (;;) {
                timedLoopStart(10);
                callDriver(DRV_BOT, BOT_PUSH, (void *) &tecla);
                if (tecla == 0x04) 
                        count_stop = 1;
                if (tecla == 0x02) 
                        count_stop = 0;
                if (tecla == 0x01) {
                        count_reset = 1;
                        count_relogio = 0;
                } else {
                        count_reset = 0;
                }
                timedLoopWait();
        }
}

char temperatura(void)
{
	unsigned int adc_output;
        uint8_t lcd_digito[4] = {0, 0, '.', 0};

        for (;;) {
                timedLoopStart(50);
                callDriver(DRV_ADC, ADC_SGET, (void *) &adc_output);
                adc_output /= 2;
                lcd_digito[0] = (adc_output / 100) % 10;
                lcd_digito[1] = (adc_output / 10) % 10;
                lcd_digito[3] = adc_output % 10;
                callDriver(DRV_LCD, LCD_SECA, (void *) lcd_digito);
                timedLoopWait();
        }
}

char pisca_leds(void)
{
        uint8_t led = 0;
        uint32_t delay;
        for (;;) {
		timedLoopStart(100);
		if (led < 3) {
                        callDriver(DRV_LED, LED_TOG, (void *) &led);
                        led++;
                        if(led == 3) 
                                led = 0;
                }
                timedLoopWait();
        }
}

char *recebe_comando(void)
{
	char EOP = '>';
	char SOP = '<';
	char *ret = NULL;
	char in_char;
	char data_is_available = 0;
	static char ended = 0;
	static char started = 0;
	static char overflow = 0;
	static unsigned char index = 0;
	static char in_data[COMMAND_MAX_SIZE] = {0};

	callDriver(DRV_SER, SER_AVAILABLE, (void *) &data_is_available);

	if (!data_is_available)
                return NULL;

	callDriver(DRV_SER, SER_READ, (void *) &in_char);

	if (!ended) {
		if (in_char == SOP) {
			index = 0;
			in_data[index] = '\0';
			started = 1;
		} else if (in_char == EOP) {
			ended = 1;
		} else if (index < COMMAND_MAX_SIZE) {
			in_data[index] = in_char;
			index++;
			in_data[index] = '\0';
		} else {
			overflow = 1;
		}
	}

	if (started && ended) {
		index = 0;
		started = 0;
		ended = 0;
		ret = in_data;
	} else if (ended || overflow) {
		ended = 0;
		started = 0;
		overflow = 0;
		ret = NULL;
	}

        return ret;
}

char processa_comando(void)
{
        uint8_t led;
        uint8_t flag_sucesso;
        char *comando;

        for (;;) {
                timedLoopStart(10);
                comando = recebe_comando();

                if (comando == NULL) {
                        timedLoopWait();
                        continue;
                }

                switch (comando[0]) {
                case 'a':
                        led = 0;
                        flag_sucesso = 1;
                        break;
                case 'b':
                        led = 1;
                        flag_sucesso = 1;
                        break;
                case 'c':
                        led = 2;
                        flag_sucesso = 1;
                        break;
                default:
                        flag_sucesso = 0;
                        break;
                }
                if (flag_sucesso) {
                        callDriver(DRV_LED, LED_TOG, (void *) &led);
                        callDriver(DRV_SER, SER_SEND_LN, "OK");
                } else {
                        callDriver(DRV_SER, SER_SEND_LN, "NOTOK");
                }
                timedLoopWait();
        }
}

char PWM_func(void)
{
        uint8_t pwm = 50;
	for (;;) {
                timedLoopStart(40);
                callDriver(DRV_PWM, PWM_SET, (void *) &pwm);
                timedLoopWait();
	}
}

int main(void)
{
        kernelInit();
        initCtrDrv();

        initDriver(DRV_LED);
        initDriver(DRV_LCD);
        initDriver(DRV_BOT);
        initDriver(DRV_ADC);
        initDriver(DRV_SER);
        initDriver(DRV_TIM);
        initDriver(DRV_PWM);
        initDriver(DRV_INT);
        /* initDriver(DRV_PID); */
        /* initDriver(DRV_WDT); */

        /* Add a new process call style:
         * kernelAddProc(ptrFunc func, int stkSize, priorityMode newPrio);
         */
        kernelAddProc((void *) processa_comando,  100, NORMAL);
        kernelAddProc((void *) temperatura,       100, NORMAL);
        kernelAddProc((void *) procRelogio,       100, RTOS);
        kernelAddProc((void *) teclado,           100, NORMAL);
        /* kernelAddProc((void *) pisca_leds,     100, NORMAL); */
        /* kernelAddProc((void *) test_PWM,       100, NORMAL); */

        kernelLoop();
}
