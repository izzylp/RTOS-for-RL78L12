/*
 * drvLcd.c
 *
 *  Created on: Jun 12, 2014
 *      Author: Pedro
 */
#include "drvLcd.h"
#include "r_cg_userdefine.h"
#include "r_cg_macrodriver.h"
#include "lcd_panel.h"

static driver thisDriver;
static ptrFuncDrv this_functions[LCD_END];

char initLcd(void *parameters);
char lcdClear(void *parameters);
char lcdOn(void *parameters);
char lcdOff(void *parameters);
char lcdDelay(void *parameters);
char lcdString(void *parameters);
char lcdSimbolos(void *parameters);
char lcdDias(void *parameters);
char lcdBateria(void *parameters);
char lcdSecA(void *parameters);
char ledSecB(void *parameters);
char ledSecC(void *parameters);

char initLcd(void *parameters)
{
	Init_Display_Panel();

	return SUCESSO;
}

char lcdClear(void *parameters)
{
	Clear_Display();

	return SUCESSO;
}

char lcdOn(void *parameters)
{
	Lcd_On();

	return SUCESSO;
}

char lcdOff(void *parameters)
{
	Lcd_Off();

	return SUCESSO;
}

/* Delay em microsegundos */
char lcdDelay(void *parameters){
	Display_Panel_Delay(*(uint32_t *) parameters);

	return SUCESSO;
}

char lcdString(void *parameters)
{
	Display_Panel_String(PANEL_LCD_LINE1, (char *const) parameters);

	return SUCESSO;
}

char lcdSimbolos(void *parameters)
{
	Symbol_Map(*(uint16_t const *) parameters);

	return SUCESSO;
}

char lcdDias(void *parameters)
{
	SECTF_Glyph_Map(*(uint8_t const *) parameters);

	return SUCESSO;
}

/* Parâmetros para a bateria LEVEL_0,LEVEL_1,LEVEL_2,LEVEL_3,LEVEL_4 */
char lcdBateria(void *parameters)
{
	SECTD_Glyph_Map(*(uint8_t const *) parameters, BATTERY_OUTLINE_ON);

	return SUCESSO;
}

/*
char lcdRelogio(void *parameters){
	SECTB_Glyph_Map ((uint8_t const) parameters, BATTERY_OUTLINE_ON);
	return sucesso;
}*/

char lcdSecA(void *parameters)
{
	uint8_t *digito = (uint8_t *) parameters;

        SECTA_Glyph_Map((uint8_t const) digito[0], CASE_0);
        SECTA_Glyph_Map((uint8_t const) digito[1], CASE_1);
        SECTA_Glyph_Map((uint8_t const) digito[2], CASE_2);
        SECTA_Glyph_Map((uint8_t const) digito[3], CASE_3);

        return SUCESSO;
}

char ledSecB(void *parameters)
{
	uint8_t *digito = (uint8_t *) parameters;

	SECTB_Glyph_Map((uint8_t const) digito[0], CASE_1);
	SECTB_Glyph_Map((uint8_t const) digito[1], CASE_2);
	SECTB_Glyph_Map((uint8_t const) digito[2], CASE_3);
	SECTB_Glyph_Map((uint8_t const) digito[3], CASE_4);
	SECTB_Glyph_Map((uint8_t const) digito[4], CASE_5);

        return SUCESSO;
}

char ledSecC(void *parameters)
{
	uint8_t *digito = (uint8_t *) parameters;

	SECTC_Glyph_Map((uint8_t const) digito[0], CASE_2);
	SECTC_Glyph_Map((uint8_t const) digito[1], CASE_3);
	SECTC_Glyph_Map((uint8_t const) digito[2], CASE_4);
	SECTC_Glyph_Map((uint8_t const) digito[3], CASE_5);

        return SUCESSO;
}

/* Função para acesso ao driver */
driver *getLcdDriver(void)
{
	thisDriver.drv_init = initLcd;

        /* Funções do driver */
	this_functions[LCD_CLEAR] = lcdClear;
	this_functions[LCD_ON] = lcdOn;
	this_functions[LCD_OFF] = lcdOff;
	this_functions[LCD_DELAY] = lcdDelay;
	this_functions[LCD_STG] = lcdString;
	this_functions[LCD_SIMB] = lcdSimbolos;
	this_functions[LCD_DIAS] = lcdDias;
	this_functions[LCD_BAT] = lcdBateria;
	this_functions[LCD_SECA] = lcdSecA;
	this_functions[LCD_SECB] = ledSecB;
	this_functions[LCD_SECC] = ledSecC;

	thisDriver.drv_func = this_functions;
	return &thisDriver;
}
