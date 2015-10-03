#ifndef DD_TYPES_H
#define DD_TYPES_H

/*  ptr. de func. para uma função do driver  */
typedef char(*ptrFuncDrv)(void *parameter);

/*  estrutura do driver  */
typedef struct{
	char drv_id;
	ptrFuncDrv *drv_func;
	ptrFuncDrv drv_init;
} driver;

/*  Função de retorno do driver  */
typedef driver *(*ptrGetDrv)(void);

#endif
