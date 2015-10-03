/*
 * drvSer.c
 *
 *  Created on: 30/07/2014
 *      Author: Luis
 */

#include "drvSer.h"
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "r_cg_serial.h"
#include "interrupt_handlers.h"
#include <string.h>

/* UART receive buffer size  */
#define RX_BUFF_SIZE	10
#define RxBuffLen	((uint8_t)(g_rx_buffer.wrPtr - g_rx_buffer.rdPtr))

/*
 * UART está configurada para operar em 38400 bps.
 * Utilizando dois canais (um de transmissão e o outro de recepção).
 * 8 bits de dados, 1 bit de parada,
 * controle por software e sem pareamento.
 */

typedef struct _Comms_Buffer
{
    /* Read Pointer */
    uint8_t rdPtr;

    /* Write Pointer */
    uint8_t wrPtr;

    /* The Buffer */
    volatile uint8_t buffer[RX_BUFF_SIZE];
}
/* Declare a structure of type _Comms_Buffer */
Comms_Buffer;

/* UART0 Tx buffer */
uint8_t  g_tx_buff[16] = {0};

/* UART0 Rx buffer */
static Comms_Buffer g_rx_buffer = {0};

/* uart0 receive data number */
volatile uint16_t  g_uart0_rx_count;

/* uart0 receive buffer address */
volatile uint8_t * gp_uart0_rx_address;

/*  uart0 send buffer address  */
volatile uint8_t * gp_uart0_tx_address;

/*  uart0 send data number  */
volatile uint16_t  g_uart0_tx_count;

static driver thisDriver;
static ptrFuncDrv this_functions[SER_END];

char initSer(void *parameters);
void INT_SR0(void);
void INT_ST0(void);
char SerRead(void *parameters);
char SerAvailable(void *parameters);
char SerSend(void *parameters);
char SerSendLn(void *parameters);

char initSer(void *parameters)
{
	R_SAU0_Create();
	//R_UART0_Create();
	R_UART0_Start();

        return SUCESSO;
}

void INT_SR0(void)
{
        if ((g_rx_buffer.wrPtr+1)%RX_BUFF_SIZE != g_rx_buffer.rdPtr) {
                g_rx_buffer.buffer[g_rx_buffer.wrPtr] = RXD0;
                g_rx_buffer.wrPtr = (g_rx_buffer.wrPtr+1)%RX_BUFF_SIZE;
        }
        /* Clear the receive flag */
        SRIF0 = CLEAR_FLAG;
}

void INT_ST0(void)
{
        /* Check if the count is greater than 0 */
        if (g_uart0_tx_count > 0U) {
                /* Send the byte in the address pointed to */
                TXD0 = *gp_uart0_tx_address;
                gp_uart0_tx_address++;
                g_uart0_tx_count--;
        }
}

/*static void uart_init_tx_buffers(void)
{
     Declare a count variable
    uint8_t j = 0;

     Clear transmit buffer
    for (j = 0; j < 16; j++)
    {
         Clear the buffer element pointed by j
        g_tx_buff[j] = 0U;
    }
}*/

char SerRead(void *parameters)
{
        uint8_t *byte_read;

        /* Declare temporary buffers */
        uint8_t itemp;

        byte_read = (uint8_t *) parameters;

        if (g_rx_buffer.wrPtr == g_rx_buffer.rdPtr)
                return 0;

        *byte_read = g_rx_buffer.buffer[g_rx_buffer.rdPtr];
        g_rx_buffer.rdPtr = (g_rx_buffer.rdPtr+1) % RX_BUFF_SIZE;

        return SUCESSO;
}

char SerAvailable(void *parameters)
{
	char *ret = (char *) parameters;
	*ret = RxBuffLen;
    /* Delay count variable */
    //uint32_t Timeout = 10000u;

    /* Wait for a byte reception or a timeout */
    //while ((CLEAR_FLAG == RxBuffLen) && (Timeout > CLEAR_FLAG))
    //{
         /* Count down until timeout */
    //     Timeout--;
    //}

    /* Return length of the Rx buffer */
    //return RxBuffLen;
        return SUCESSO;
}

char SerSend(void *parameters)
{
	char *buffer;
	uint8_t size;
	uint8_t new_size;

	buffer = (char *) parameters;
	size = strlen(buffer);
	new_size = size+1;

	char new_buffer[new_size];
	strncpy(new_buffer, buffer, size);
	new_buffer[size] = ASCII_CARRIAGE_RETURN;

	R_UART0_Send(new_buffer, new_size);

        return SUCESSO;
}

char SerSendLn(void *parameters)
{
	char *buffer;
	uint8_t size;
	uint8_t new_size;

	buffer = (char *) parameters;
	size = strlen(buffer);
	new_size = size+2;

	char new_buffer[new_size];
	strncpy(new_buffer, buffer, size);
	new_buffer[size] = ASCII_CARRIAGE_RETURN;
	new_buffer[size+1] = ASCII_NEW_LINE;

	R_UART0_Send(new_buffer, new_size);

        return SUCESSO;
}

/* Função para acesso ao driver */
driver *getSerDriver(void)
{
	thisDriver.drv_init = initSer;

        /* Funções do driver */
	this_functions[SER_READ] = SerRead;
	this_functions[SER_SEND] = SerSend;
	this_functions[SER_SEND_LN] = SerSendLn;
	this_functions[SER_AVAILABLE] = SerAvailable;

	thisDriver.drv_func = this_functions;
	return &thisDriver;
}
