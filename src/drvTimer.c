/*
 * drvTimer.c
 *
 *  Created on: 20/09/2014
 *      Author: Luis
 */

#include "drvTimer.h"
#include "r_cg_it.h"
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"

static driver thisDriver;
static ptrFuncDrv this_functions[TIMER_END];

char initTimer(void *parameters);
char startTimer(void *parameters);
char stopTimer(void *parameters);

char initTimer(void *parameters)
{
	return SUCESSO;
}

char startTimer(void *parameters)
{
        R_IT_Start();
}

char stopTimer(void *parameters)
{
        R_IT_Stop();
}

driver *getTimDriver(void)
{
	thisDriver.drv_init = initTimer;

	this_functions[TIMER_START] = startTimer;
	this_functions[TIMER_STOP] = stopTimer;

	thisDriver.drv_func = this_functions;

	return &thisDriver;
}
