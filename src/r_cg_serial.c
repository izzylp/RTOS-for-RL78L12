/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software.  By using this software, 
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_serial.c
* Version      : Applilet3 for RL78/L12 V1.00.00 [23 Mar 2012]
* Device(s)    : R5F10RLC
* Tool-Chain   : GNURL78 v13.01
* Description  : This file implements device driver for Serial module.
* Creation Date: 21/01/2013
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
/* Defines the I/O register structures */
#include "iodefine.h"
/* Defines the extended I/O register structures */
#include "iodefine_ext.h"

/* Header files inclusion */
#include "r_cg_macrodriver.h"
#include "r_cg_serial.h"
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* uart0 transmit buffer address */
volatile uint8_t * gp_uart0_tx_address;

/* uart0 transmit data number */
volatile uint16_t  g_uart0_tx_count;

/* uart0 receive buffer address */
volatile uint8_t * gp_uart0_rx_address;

/* uart0 receive data number */
volatile uint16_t  g_uart0_rx_count;

/* uart0 receive data length */
volatile uint16_t  g_uart0_rx_length;

/***********************************************************************************************************************
* Function Name: R_SAU0_Create
* Description  : This function initialises the SAU0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU0_Create (void)
{
    /* supply SAU0 clock */
    SAU0EN = 1U;
    
    /* Add 4 instruction cycle delays */
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    
    /* Configure the SAU clock source */
    SPS0 = _0002_SAU_CK00_FCLK_2 | _0020_SAU_CK01_FCLK_2;
    
    /* Call function to initialise SAU channel 0 */
    R_UART0_Create();
}
/***********************************************************************************************************************
* End of function R_SAU0_Create
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: R_UART0_Create
* Description  : This function initialises the UART0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART0_Create (void)
{
    /* disable UART0 receive and transmit */
    ST0 |= _0002_SAU_CH1_STOP_TRG_ON | _0001_SAU_CH0_STOP_TRG_ON;
    
    /* disable INTST0 interrupt */
    STMK0 = 1U;
    
    /* clear INTST0 interrupt flag */
    STIF0 = 0U;
    
    /* disable INTSR0 interrupt */
    SRMK0 = 1U;
    
    /* clear INTSR0 interrupt flag */
    SRIF0 = 0U;
    
    /* disable INTSRE0 interrupt */
    SREMK0 = 1U;
    
    /* clear INTSRE0 interrupt flag */
    SREIF0 = 0U;
    
    /* Set INTST0 low priority */
    STPR10 = 1U;
    STPR00 = 1U;
    
    /* Set INTSR0 low priority */
    SRPR10 = 1U;
    SRPR00 = 1U;
    
    /* Configure channel 0 */
    SMR00 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_TRIGGER_SOFTWARE |
            _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;
    SCR00 = _8000_SAU_TRANSMISSION | _0000_SAU_INTSRE_MASK | _0000_SAU_PARITY_NONE | _0080_SAU_LSB | _0010_SAU_STOP_1 |
            _0007_SAU_LENGTH_8;
    SDR00 = _9A00_UART0_TRANSMIT_DIVISOR;
    NFEN0 |= _01_SAU_RXD0_FILTER_ON;
    SIR01 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;    /* clear error flag */
    SMR01 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0100_SAU_TRIGGER_RXD | _0000_SAU_EDGE_FALL |
            _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;
    SCR01 = _4000_SAU_RECEPTION | _0000_SAU_INTSRE_MASK | _0000_SAU_PARITY_NONE | _0080_SAU_LSB | _0010_SAU_STOP_1 |
            _0007_SAU_LENGTH_8;
    SDR01 = _9A00_UART0_RECEIVE_DIVISOR;
    SO0 |= _0001_SAU_CH0_DATA_OUTPUT_1;
    
    /* output level normal */
    SOL0 |= _0000_SAU_CHANNEL0_NORMAL;
    
    /* enable UART0 output */
    SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;
    
    /* Set RxD0 pin */
    PFSEG3 &= 0xDFU;
    PM1 |=0x02U;
    
    /* Set TxD0 pin */
    PFSEG3 &= 0xBFU;
    P1 |= 0x04U;
    PM1 &= 0xFBU;
}
/***********************************************************************************************************************
* End of function R_UART0_Create
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: R_UART0_Start
* Description  : This function starts the UART0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART0_Start (void)
{
    /* clear INTST0 interrupt flag */
    STIF0 = 0U;
    
    /* enable INTST0 interrupt */
    STMK0 = 0U;
    
    /* clear INTSR0 interrupt flag */
    SRIF0 = 0U;
    
    /* enable INTSR0 interrupt */
    SRMK0 = 0U;
    
    /* output level normal */
    SO0 |= _0001_SAU_CH0_DATA_OUTPUT_1;
    
    /* enable UART0 output */
    SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;
    
    /* enable UART0 receive and transmit */
    SS0 |= _0002_SAU_CH1_START_TRG_ON | _0001_SAU_CH0_START_TRG_ON;
}
/***********************************************************************************************************************
* End of function R_UART0_Start
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: R_UART0_Stop
* Description  : This function stops the UART0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UART0_Stop (void)
{
    /* disable UART0 receive and transmit */
    ST0 |= _0002_SAU_CH1_STOP_TRG_ON | _0001_SAU_CH0_STOP_TRG_ON;
    
    /* disable UART0 output */
    SOE0 &= ~_0001_SAU_CH0_OUTPUT_ENABLE;
    
    /* disable INTST0 interrupt */
    STMK0 = 1U;
    
    /* clear INTST0 interrupt flag */
    STIF0 = 0U;
    
    /* disable INTSR0 interrupt */
    SRMK0 = 1U;
    
    /* clear INTSR0 interrupt flag */
    SRIF0 = 0U;
}
/***********************************************************************************************************************
* End of function R_UART0_Stop
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: R_UART0_Send
* Description  : This function sends UART0 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_UART0_Send (uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;
    
    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        gp_uart0_tx_address = tx_buf;
        g_uart0_tx_count = tx_num;
        
        /* disable INTST0 interrupt */
        STMK0 = 1U;
        TXD0 = *gp_uart0_tx_address;
        gp_uart0_tx_address++;
        g_uart0_tx_count--;
        
        /* enable INTST0 interrupt */
        STMK0 = 0U;

        while (g_uart0_tx_count);
    }
    
    return (status);
}
/***********************************************************************************************************************
* End of function R_UART0_Send
***********************************************************************************************************************/


