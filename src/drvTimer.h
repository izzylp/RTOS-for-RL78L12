/*
 * drvTimer.h
 *
 *  Created on: 20/09/2014
 *      Author: Luis
 */

#ifndef DRVTIMER_H_
#define DRVTIMER_H_

#include "dd_types.h"

enum {
        TIMER_START,
        TIMER_STOP,
	TIMER_END
};

/* Função de acesso ao driver */
driver *getTimDriver(void);

#endif
