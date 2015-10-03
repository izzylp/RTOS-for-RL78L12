/*
 * drvPID.h
 *
 *  Created on: 05/09/2014
 *      Author: Luis Paulo
 */

#ifndef DRVPID_H_
#define DRVPID_H_

#include "dd_types.h"

enum {
	PID_START,
	PID_STOP,
	PID_UPDATE,
	PID_RESET,
	PID_GETVALUES,
	PID_SETVALUES,
	PID_SETPOINTS,
	PID_END
};

/* Função de acesso ao driver */
driver *getPIDDriver(void);

#endif
