/*
 * drvInterrupt.c
 *
 *  Created on: 20/09/2014
 *      Author: Luis
 */

#include "drvInterrupt.h"
#include "r_cg_userdefine.h"
#include "r_cg_macrodriver.h"

static driver thisDriver;
static ptrFuncDrv this_functions[INT_END];

char initInterrupt(void *parameters);
char intEnable(void *parameters);
char intDisable(void *parameters);
char intBotSet(void *parameters);
char intBotEnable(void *parameters);
char intBotDisable(void *parameters);
char intADCSet(void *parameters);
char intADCEnable(void *parameters);
char intADCDisable(void *parameters);
char intSerRXSet(void *parameters);
char intSerRXEnable(void *parameters);
char intSerRXDisable(void *parameters);
char intSerTXSet(void *parameters);
char intSerTXEnable(void *parameters);
char intSerTXDisable(void *parameters);
char intTimSet(void *parameters);
char intTimEnable(void *parameters);
char intTimDisable(void *parameters);
char intPWMSet(void *parameters);
char intPWMEnable(void *parameters);
char intPWMDisable(void *parameters);

char initInterrupt(void *parameters)
{
        asm("di");

	return SUCESSO;
}

char intEnable(void *parameters)
{
        asm("ei");

        return SUCESSO;
}

char intDisable(void *parameters)
{
        asm("di");

        return SUCESSO;
}

driver *getIntDriver(void)
{
	thisDriver.drv_init = initInterrupt;

	//this_functions[INT_ENABLE] = intEnable;
	//this_functions[INT_DISABLE] = intDisable;

	thisDriver.drv_func = this_functions;
	return &thisDriver;
}
