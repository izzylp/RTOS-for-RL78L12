/*
 * drvADC.c
 *
 *  Created on: Jul 15, 2014
 *      Author: Pedro
 */
#include "drvADC.h"
#include "r_cg_userdefine.h"
#include "r_cg_macrodriver.h"
#include "r_cg_adc.h"

static driver thisDriver;
static ptrFuncDrv this_functions[ADC_END];

char initADC(void *parameters);
char ADCStart(void *parameters);
char ADCSGet(void *parameters);
char ADCGet(void *parameters);
char ADCStop(void *parameters);

char initADC(void *parameters)
{
	R_ADC_Create();
	R_ADC_Set_Operation_On();

	return SUCESSO;
}

char ADCStart(void *parameters)
{
	R_ADC_Start();

	return SUCESSO;
}

char ADCSGet(void *parameters)
{
	R_ADC_Start();
	R_ADC_Get_Result((uint16_t *const) parameters);

	return SUCESSO;
}

char ADCGet(void *parameters)
{
	R_ADC_Get_Result((uint16_t *const) parameters);

	return SUCESSO;
}

char ADCStop(void *parameters)
{
	R_ADC_Stop();

	return SUCESSO;
}

/* Função para acesso ao driver */
driver *getADCDriver(void)
{
	thisDriver.drv_init = initADC;

	/* Funções do driver */
	this_functions[ADC_START] = ADCStart;
	this_functions[ADC_SGET] = ADCSGet;
	this_functions[ADC_GET] = ADCGet;
	this_functions[ADC_STOP] = ADCStop;

	thisDriver.drv_func = this_functions;
	return &thisDriver;
}
