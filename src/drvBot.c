/*
 * drvBot.c
 *
 *  Created on: Jun 26, 2014
 *      Author: Pedro
 */
#include "drvBot.h"
#include "r_cg_userdefine.h"
#include "r_cg_macrodriver.h"

static driver thisDriver;
static ptrFuncDrv this_functions[BOT_END];

char initBot(void *parameters);
char botPush(void *parameters);
char botSelect(void *parameters);

char initBot(void *parameters)
{
	return SUCESSO;
}

char botPush(void *parameters)
{
	uint8_t ret = 0;

	if (!SW1) {
		ret |= 0x01;
	}
	if (!SW2) {
		ret |= 0x02;
	}
	if (!SW3) {
		ret |= 0x04;
	}

        *((uint8_t *) parameters) = ret;

        return SUCESSO;
}

char botSelect(void *parameters)
{
        uint8_t button = *(uint8_t *) parameters;
        uint8_t switch_is_pressed;

        /* Utilizando o valor de PRM via referencia */
	switch (button) {
	case 1:
		if (!SW1)
			switch_is_pressed = 1;
		else
			switch_is_pressed = 0;
		break;
	case 2:
		if (!SW2)
			switch_is_pressed = 1;
		else
			switch_is_pressed = 0;
		break;
	case 3:
		if (!SW3)
			switch_is_pressed = 1;
	        else
			switch_is_pressed = 0;
		break;
	default:
		switch_is_pressed = 0;
                break;
	}
	button = switch_is_pressed;

	return SUCESSO;
}

/* Função para acesso ao driver */
driver *getBotDriver(void)
{
	thisDriver.drv_init = initBot;

	/* Funções do driver */
	this_functions[BOT_PUSH] = botPush;
	this_functions[BOT_SEL] = botSelect;

	thisDriver.drv_func = this_functions;
	return &thisDriver;
}
