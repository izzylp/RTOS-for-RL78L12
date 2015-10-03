/*
 * drvPWM.h
 *
 *  Created on: 14/09/2014
 *      Author: Luis
 */

#ifndef DRVPWM_H_
#define DRVPWM_H_

#include "dd_types.h"
#include "r_cg_userdefine.h"

enum {
	PWM_SET,
	PWM_GET,
	PWM_END
};

/* Função de acesso ao driver */
driver *getPWMDriver(void);

#endif
