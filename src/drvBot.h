/*
 * drvBot.h
 *
 *  Created on: Jun 26, 2014
 *      Author: Pedro
 */

#ifndef DRVBOT_H_
#define DRVBOT_H_

#include "dd_types.h"

/* Lista de funções do driver */
enum {
        BOT_PUSH, 
        BOT_SEL, 
        BOT_END
};

/* Função de acesso ao driver */
driver *getBotDriver(void);

#endif
