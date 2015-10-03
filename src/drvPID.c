/*
 * drvPID.c
 *
 *  Created on: 05/09/2014
 *      Author: Luis Paulo
 */

#include "drvPID.h"
#include "ctrdrv.h"
#include "r_cg_userdefine.h"
#include "r_cg_macrodriver.h"

static driver thisDriver;
static ptrFuncDrv this_functions[PID_END];

static int e0, e1, e2;
static int y0, y1, y2;
static int kp, ki, kd;
static int kp_new, ki_new, kd_new;
static int T_new;
static int T;
static int sp, sp_new;

static unsigned char flag, run;

char startPID(void *parameters);
char stopPID(void *parameters);
char updatePID(void *parameters);
char resetPID(void *parameters);
char getPIDValues(void *parameters);
char setPIDValues(void *parameters);
char spChange(void *parameters);

char startPID(void *parameters)
{
        /* Starts the control to send signals by serial port */
	run = 1;
	return SUCESSO;
}

char spChange(void *parameters)
{
	/* Changes the system setpoint */
	sp = (unsigned int) parameters;
	return SUCESSO;
}

char stopPID(void *parameters)
{
	/* To stop the control sending signals by serial */
	run = 0;
	return SUCESSO;
}

char resetPID(void *parameters)
{
	y0 = 0;
	y1 = 0;
	y2 = 0;
	e0 = 0;
	e1 = 0;
	e2 = 0;

	return SUCESSO;
}

char updatePID(void *parameters)
{
	int pwm;
	int ad;
	
        /*  Change control values  */
	if (flag == 1) {
		kp = kp_new;
		ki = ki_new;
		kd = kd_new;
		T = T_new;
		flag = 0;
	}
	if (run == 1) {
		/*  Update variables  */
		y2 = y1;
		y1 = y0;
		e2 = e1;
		e1 = e0;

		callDriver(DRV_PWM, PWM_GET, &pwm);

		e0 = (sp - ad)/1023.0;

		/*  Processing  */
		y0 = y2 + (kp * (e0-e2)) + \
				 (ki * (e0 + (2*e1) + e2) * T/2) + \
				 (kd * (e0 - (2*e1) + e2) * 2/T);

		/*  Saturations  */
		if (y0 > 1) {
			callDriver(DRV_PWM, PWM_SET, 100); 
			//int2ascii(1023, &msgPID[1+1]);
		} else if (y0 < 0) {
			callDriver(DRV_PWM, PWM_SET, (void*) 0);
			//int2ascii(0, &msgPID[1+1]);
		} else {
			callDriver(DRV_PWM, PWM_SET, (void *)((int)(y0*1023)));
			//int2ascii((int)(y0*1023), &msgPID[1+1]);
		}
		//int2ascii(ad, &msgPID[5+2]);
		//int2ascii(sp, &msgPID[9+3]);

		//sendMsg(msgPID, (12+4));
	}
	return SUCESSO;
}

char getPIDValues(void *parameters)
{
	((int *) parameters)[0] = (int)(kp*100);
	((int *) parameters)[1] = (int)(ki*100);
	((int *) parameters)[2] = (int)(kd*100);
	((int *) parameters)[3] = (int)(T*1000);

	return SUCESSO;
}

char setPIDValues(void *parameters)
{
	/* Set new values to the temporary variables to update later */
	kp_new = ((int *) parameters)[0] / 100.0;
	ki_new = ((int *) parameters)[1] / 100.0;
	kd_new = ((int *) parameters)[2] / 100.0;
	T_new = ((int *) parameters)[3] / 1000.0;
	flag = 1;

	return SUCESSO;
}

char initPID(void *parameters)
{
	/*  Variables adjust and driver's struct  */
	e0 = e1 = e2 = y0 = y1 = y2 = 0;
	T = 0.01;
	sp = 0;
	kp = 1;
	ki = 5;
	kd = 0;
	flag = 0;
	run = 0;

	return SUCESSO;
}

driver *getPIDDriver(void)
{
	thisDriver.drv_init = initPID;

	this_functions[PID_START] = startPID;
	this_functions[PID_STOP] = stopPID;
	this_functions[PID_UPDATE] = updatePID;
	this_functions[PID_RESET] = resetPID;
	this_functions[PID_GETVALUES] = getPIDValues;
	this_functions[PID_SETVALUES] = setPIDValues;
	this_functions[PID_SETPOINTS] = spChange;

	thisDriver.drv_func = this_functions;

	return &thisDriver;
}
