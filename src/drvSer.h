/*
 * drvSer.h
 *
 *  Created on: 30/07/2014
 *      Author: Luis
 */

#ifndef DRVSER_H_
#define DRVSER_H_

#include "dd_types.h"

enum {
        SER_READ,
        SER_SEND,
        SER_SEND_LN,
        SER_AVAILABLE,
        SER_END
};

/* Função de acesso ao driver */
driver *getSerDriver(void);

#endif
