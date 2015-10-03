#include "drvLed.h"
#include "r_cg_userdefine.h"
#include "r_cg_macrodriver.h"

static driver thisDriver;
static ptrFuncDrv this_functions[LED_END];

char initLed(void *parameters);
char ligaLed(void *parameters);
char desligaLed(void *parameters);
char toggleLed(void *parameters);

char initLed(void *parameters)
{
	LED1_DIR = 0u;
	LED2_DIR = 0u;

	LED0 = 1u;
	LED1 = 1u;
	LED2 = 1u;

	return SUCESSO;
}

char ligaLed(void *parameters)
{
	uint8_t led;
	led = *(uint8_t *) parameters;
	switch (led) {
	case 0:
		LED0 = LED_TURN_ON;
		break;
	case 1:
		LED1 = LED_TURN_ON;
		break;
	case 2:
		LED2 = LED_TURN_ON;
		break;
        default:
                break;
	}
	return SUCESSO;
}

char desligaLed(void *parameters)
{
	uint8_t led;
	led = *(uint8_t *) parameters;
	switch (led) {
	case 0:
		LED0 = LED_TURN_OFF;
		break;
	case 1:
		LED1 = LED_TURN_OFF;
		break;
	case 2:
		LED2 = LED_TURN_OFF;
		break;
        default:
                break;
	}
	return SUCESSO;
}

char toggleLed(void *parameters)
{
	uint8_t led;
	led = *(uint8_t *) parameters;
	switch (led) {
	case 0:
		LED0 = ~LED0;
		break;
	case 1:
		LED1 = ~LED1;
		break;
	case 2:
		LED2 = ~LED2;
		break;
        default:
                break;
	}
	return SUCESSO;
}

/* Função para acesso ao driver */
driver* getLedDriver(void)
{
	thisDriver.drv_init = initLed;
	
        /* Funções do driver */
	this_functions[LED_ON] = ligaLed;
	this_functions[LED_OFF] = desligaLed;
	this_functions[LED_TOG] = toggleLed;

	thisDriver.drv_func = this_functions;
	return &thisDriver;
}
