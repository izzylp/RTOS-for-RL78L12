/*
 * drvPWM.h
 *
 *  Created on: 14/09/2014
 *      Author: Luis
 */

#include "drvPWM.h"
#include "r_cg_userdefine.h"
#include "r_cg_macrodriver.h"
#include "r_cg_timer.h"

static driver thisDriver;
static ptrFuncDrv this_functions[PWM_END];

static uint8_t pwm;

char setPWM(void *parameters);
char getPWM(void *parameters);
char initPWM(void *parameters);

static void r_tau0_create(void)
{
        /* Enables TAU0 */
        TAU0EN = 1U;

        /* fclk (24MHz), CK0 = 24MHz, CK1 = 24MHz */
        TPS0 = _0000_TAU_CKM0_FCLK_0;

        /* Set INTTM00 low priority */
        TMPR100 = 1U;
        TMPR000 = 1U;

        /* Set INTTM03 low priority */
        TMPR103 = 1U;
        TMPR003 = 1U;

        /* Channel 0 is used as master channel for PWM output function */
        TMR00 = _0000_TAU_CLOCK_SELECT_CKM0 
                        | _0000_TAU_CLOCK_MODE_CKS 
                        | _0000_TAU_TRIGGER_SOFTWARE 
                        | _0001_TAU_MODE_PWM_MASTER;

        /* Channel 3 is used as slave channel for PWM output function */
        TMR03 = _0000_TAU_CLOCK_SELECT_CKM0 
                        | _0000_TAU_CLOCK_MODE_CKS 
                        | _0000_TAU_COMBINATION_SLAVE 
                        | _0400_TAU_TRIGGER_MASTER_INT 
                        | _0009_TAU_MODE_PWM_SLAVE;

        TDR00 = 19999U;
        TDR03 = 0U;

        /* Saída em nível 0 */
        TO0 &= ~_0001_TAU_CH0_OUTPUT_VALUE_1;
        /* Saída desabilitada */
        TOE0 &= ~_0001_TAU_CH0_OUTPUT_ENABLE;

        /* Modo escravo do CH3 */
        TOM0 |= _0008_TAU_CH3_OUTPUT_COMBIN;
        /* Lógica positiva do CH3 (ativo em nível 1) */
        TOL0 &= ~_0008_TAU_CH3_OUTPUT_LEVEL_L;
        /* Saída em nível 0 */
        TO0 &= ~_0008_TAU_CH3_OUTPUT_VALUE_1;
        /* Saída desabilitada */
        TOE0 &= ~_0008_TAU_CH3_OUTPUT_ENABLE;

        /* Set TO03 pin */
        PM3 &= 0xfdU;
        P3 &= 0xfdU;
}

static void r_tau0_channel0_start(void)
{
        /* Clear INTTM00 interrupt flag */
        TMIF00 = 0U;
        /* Enable INTTM00 interrupt */
        TMMK00 = 0U;
        /* Saída habilitada */
        TOE0 |= _0001_TAU_CH0_OUTPUT_ENABLE;
        /* Inicia operação conforme configurado */
        TS0 |= _0001_TAU_CH0_START_TRG_ON;
}

static void r_tau0_channel3_start(void)
{
        /* Clear INTTM03 interrupt flag */
        TMIF03 = 0U;
        /* Enable INTTM03 interrupt */
        TMMK03 = 0U;
        /* Saída habilitada */
        TOE0 |= _0008_TAU_CH3_OUTPUT_ENABLE;
        /* Inicia operação conforme configurado */
        TS0 |= _0008_TAU_CH3_START_TRG_ON;
}

char setPWM(void *parameters)
{
        uint8_t new_pwm = *(uint8_t *) parameters;

	if (new_pwm > 100)
		return FALHA;

        pwm = new_pwm;
	TDR03 = (pwm * (TDR00 + 1)) / 100;

	return SUCESSO;
}

char getPWM(void *parameters)
{
        uint8_t ret = *(uint8_t *) parameters;

        ret = pwm;

        return SUCESSO;
}

char initPWM(void *parameters)
{
	r_tau0_create;
	r_tau0_channel0_start;
	r_tau0_channel3_start;

	return SUCESSO;
}

driver *getPWMDriver(void)
{
	thisDriver.drv_init = initPWM;

	this_functions[PWM_SET] = setPWM;
	this_functions[PWM_GET] = getPWM;

	thisDriver.drv_func = this_functions;

	return &thisDriver;
}
