/*
* drvLcd.h
*
*  Created on: Jun 12, 2014
*      Author: Pedro
*/
#ifndef DRVLCD_H_
#define DRVLCD_H_

#include "dd_types.h"

/*
 * Lista de funções do driver:
 * LCD_SECA -> XX.X
 * LCD_SECB -> XX:XX RELOGIO
 * LCD_SECC -> XXXX NÚMEROS E LETRAS
 * LCD_SECD -> BATERIA
 * LCD_SECF -> DIAS
 * LCD_SIMB -> SIMBOLOS
 */
enum {
	LCD_CLEAR,
        LCD_ON,
        LCD_OFF,
        LCD_SECA,
        LCD_SECB,
        LCD_SECC,
	LCD_BAT,
        LCD_DIAS,
        LCD_SIMB,
        LCD_STG,
        LCD_DELAY,
        LCD_END
};

/* Função de acesso ao driver */
driver *getLcdDriver(void);

#endif
