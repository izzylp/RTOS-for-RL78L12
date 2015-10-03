/*
 * drvInterrupt.h
 *
 *  Created on: 20/09/2014
 *      Author: Luis
 */

#ifndef DRVINTERRUPT_H_
#define DRVINTERRUPT_H_

#include "dd_types.h"

enum {
        /*INT_ENABLE,
        INT_DISABLE,
        INT_BOT_SET,
        INT_BOT_ENABLE,
        INT_BOT_DISABLE,
        INT_ADC_SET,
        INT_ADC_ENABLE,
        INT_ADC_DISABLE,
        INT_SER_RX_SET,
        INT_SER_RX_ENABLE,
        INT_SER_RX_DISABLE,
        INT_SER_TX_SET,
        INT_SER_TX_ENABLE,
        INT_SER_TX_DISABLE,
        INT_TIM_SET,
        INT_TIM_ENABLE,
        INT_TIM_DISABLE,
        INT_PWM_SET,
        INT_PWM_ENABLE,
        INT_PWM_DISABLE,*/
	INT_END
};

/* Função de acesso ao driver */
driver *getIntDriver(void);

#endif
