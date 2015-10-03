#ifndef DRVLED_H_
#define DRVLED_H_

#include "dd_types.h"
	
/* Lista de funções do driver */
enum {
	LED_ON, 
        LED_OFF, 
        LED_TOG, 
        LED_END
};

/* Função de acesso ao driver */
driver *getLedDriver(void);

#endif
