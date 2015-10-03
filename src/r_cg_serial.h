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
* File Name    : r_cg_serial.h
* Version      : Applilet3 for RL78/L12 V1.00.00 [23 Mar 2012]
* Device(s)    : R5F10RLC
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for Serial module.
* Creation Date: 21/01/2013
***********************************************************************************************************************/

#ifndef SERIAL_H
#define SERIAL_H

/* Includes widely used macro definitions */
#include "r_cg_macrodriver.h"

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Serial Clock Select Register m (SPSm)
*/
/* Operating mode and clear mode selection (PRSm03 - PRSm00) */
#define _0000_SAU_CK00_FCLK_0                    (0x0000U) /* ck00 - fCLK */
#define _0001_SAU_CK00_FCLK_1                    (0x0001U) /* ck00 - fCLK/2^1 */
#define _0002_SAU_CK00_FCLK_2                    (0x0002U) /* ck00 - fCLK/2^2 */
#define _0003_SAU_CK00_FCLK_3                    (0x0003U) /* ck00 - fCLK/2^3 */
#define _0004_SAU_CK00_FCLK_4                    (0x0004U) /* ck00 - fCLK/2^4 */
#define _0005_SAU_CK00_FCLK_5                    (0x0005U) /* ck00 - fCLK/2^5 */
#define _0006_SAU_CK00_FCLK_6                    (0x0006U) /* ck00 - fCLK/2^6 */
#define _0007_SAU_CK00_FCLK_7                    (0x0007U) /* ck00 - fCLK/2^7 */
#define _0008_SAU_CK00_FCLK_8                    (0x0008U) /* ck00 - fCLK/2^8 */
#define _0009_SAU_CK00_FCLK_9                    (0x0009U) /* ck00 - fCLK/2^9 */
#define _000A_SAU_CK00_FCLK_10                   (0x000AU) /* ck00 - fCLK/2^10 */
#define _000B_SAU_CK00_FCLK_11                   (0x000BU) /* ck00 - fCLK/2^11 */
#define _000C_SAU_CK00_FCLK_12                   (0x000CU) /* ck00 - fCLK/2^12 */
#define _000D_SAU_CK00_FCLK_13                   (0x000DU) /* ck00 - fCLK/2^13 */
#define _000E_SAU_CK00_FCLK_14                   (0x000EU) /* ck00 - fCLK/2^14 */
#define _000F_SAU_CK00_FCLK_15                   (0x000FU) /* ck00 - fCLK/2^15 */
/* Operating mode and clear mode selection (PRSm13 - PRSm10) */
#define _0000_SAU_CK01_FCLK_0                    (0x0000U) /* ck01 - fCLK */
#define _0010_SAU_CK01_FCLK_1                    (0x0010U) /* ck01 - fCLK/2^1 */
#define _0020_SAU_CK01_FCLK_2                    (0x0020U) /* ck01 - fCLK/2^2 */
#define _0030_SAU_CK01_FCLK_3                    (0x0030U) /* ck01 - fCLK/2^3 */
#define _0040_SAU_CK01_FCLK_4                    (0x0040U) /* ck01 - fCLK/2^4 */
#define _0050_SAU_CK01_FCLK_5                    (0x0050U) /* ck01 - fCLK/2^5 */
#define _0060_SAU_CK01_FCLK_6                    (0x0060U) /* ck01 - fCLK/2^6 */
#define _0070_SAU_CK01_FCLK_7                    (0x0070U) /* ck01 - fCLK/2^7 */
#define _0080_SAU_CK01_FCLK_8                    (0x0080U) /* ck01 - fCLK/2^8 */
#define _0090_SAU_CK01_FCLK_9                    (0x0090U) /* ck01 - fCLK/2^9 */
#define _00A0_SAU_CK01_FCLK_10                   (0x00A0U) /* ck01 - fCLK/2^10 */
#define _00B0_SAU_CK01_FCLK_11                   (0x00B0U) /* ck01 - fCLK/2^11 */
#define _00C0_SAU_CK01_FCLK_12                   (0x00C0U) /* ck01 - fCLK/2^12 */
#define _00D0_SAU_CK01_FCLK_13                   (0x00D0U) /* ck01 - fCLK/2^13 */
#define _00E0_SAU_CK01_FCLK_14                   (0x00E0U) /* ck01 - fCLK/2^14 */
#define _00F0_SAU_CK01_FCLK_15                   (0x00F0U) /* ck01 - fCLK/2^15 */

/*
    Serial Mode Register mn (SMRmn)
*/
#define _0020_SAU_SMRMN_INITIALVALUE             (0x0020U)
/* Selection of macro clock (MCK) of channel n (CKSmn) */
#define _0000_SAU_CLOCK_SELECT_CK00              (0x0000U) /* operation clock CK0 set by PRS register */ 
#define _8000_SAU_CLOCK_SELECT_CK01              (0x8000U) /* operation clock CK1 set by PRS register */
/* Selection of transfer clock (TCLK) of channel n (CCSmn) */
#define _0000_SAU_CLOCK_MODE_CKS                 (0x0000U) /* divided operation clock MCK specified by CKSmn bit */  
#define _4000_SAU_CLOCK_MODE_TI0N                (0x4000U) /* clock input from SCK pin (slave transfer in CSI mode) */
/* Selection of start trigger source (STSmn) */
#define _0000_SAU_TRIGGER_SOFTWARE               (0x0000U) /* only software trigger is valid */
#define _0100_SAU_TRIGGER_RXD                    (0x0100U) /* valid edge of RXD pin */
/* Controls inversion of level of receive data of channel n in UART mode (SISmn0) */
#define _0000_SAU_EDGE_FALL                      (0x0000U) /* falling edge is detected as the start bit */
#define _0040_SAU_EDGE_RISING                    (0x0040U) /* rising edge is detected as the start bit */
/* Setting of operation mode of channel n (MDmn2, MDmn1) */
#define _0000_SAU_MODE_CSI                       (0x0000U) /* CSI mode */
#define _0002_SAU_MODE_UART                      (0x0002U) /* UART mode */
#define _0004_SAU_MODE_IIC                       (0x0004U) /* simplified IIC mode */
/* Selection of interrupt source of channel n (MDmn0) */
#define _0000_SAU_TRANSFER_END                   (0x0000U) /* transfer end interrupt */
#define _0001_SAU_BUFFER_EMPTY                   (0x0001U) /* buffer empty interrupt */

/*
    Serial Communication Operation Setting Register mn (SCRmn)
*/
/* Setting of operation mode of channel n (TXEmn, RXEmn) */
#define _0000_SAU_NOT_COMMUNICATION              (0x0000U) /* does not start communication */
#define _4000_SAU_RECEPTION                      (0x4000U) /* reception only */
#define _8000_SAU_TRANSMISSION                   (0x8000U) /* transmission only */
#define _C000_SAU_RECEPTION_TRANSMISSION         (0xC000U) /* reception and transmission */
/* Selection of data and clock phase in CSI mode (DAPmn, CKPmn) */
#define _0000_SAU_TIMING_1                       (0x0000U) /* type 1 */
#define _1000_SAU_TIMING_2                       (0x1000U) /* type 2 */
#define _2000_SAU_TIMING_3                       (0x2000U) /* type 3 */
#define _3000_SAU_TIMING_4                       (0x3000U) /* type 4 */
/* Selection of masking of error interrupt signal (EOCmn) */
#define _0000_SAU_INTSRE_MASK                    (0x0000U) /* masks error interrupt INTSREx */
#define _0400_SAU_INTSRE_ENABLE                  (0x0400U) /* enables generation of error interrupt INTSREx */
/* Setting of parity bit in UART mode (PTCmn1 - PTCmn0) */
#define _0000_SAU_PARITY_NONE                    (0x0000U) /* none parity */
#define _0100_SAU_PARITY_ZERO                    (0x0100U) /* zero parity */
#define _0200_SAU_PARITY_EVEN                    (0x0200U) /* even parity */
#define _0300_SAU_PARITY_ODD                     (0x0300U) /* odd parity */
/* Selection of data transfer sequence in CSI and UART modes (DIRmn) */
#define _0000_SAU_MSB                            (0x0000U) /* MSB */
#define _0080_SAU_LSB                            (0x0080U) /* LSB */
/* Setting of stop bit in UART mode (SLCmn1, SLCmn0) */
#define _0000_SAU_STOP_NONE                      (0x0000U) /* none stop bit */
#define _0010_SAU_STOP_1                         (0x0010U) /* 1 stop bit */
#define _0020_SAU_STOP_2                         (0x0020U) /* 2 stop bits */
/* Setting of data length in CSI and UART modes (DLSmn1 - DLSmn0) */
#define _0005_SAU_LENGTH_9                       (0x0005U) /* 9-bit data length */
#define _0006_SAU_LENGTH_7                       (0x0006U) /* 7-bit data length */
#define _0007_SAU_LENGTH_8                       (0x0007U) /* 8-bit data length */

/*
    Serial Output Level Register m (SOLm)
*/
/* Selects inversion of the level of the transmit data of channel n in UART mode */

/* normal bit level */
#define _0000_SAU_CHANNEL0_NORMAL                (0x0000U)
/* inverted bit level */
#define _0001_SAU_CHANNEL0_INVERTED              (0x0001U)

/*
    Noise Filter Enable Register 0 (NFEN0)
*/
/* Use of noise filter */

/* noise filter off */
#define _00_SAU_RXD0_FILTER_OFF                  (0x00U)
/* noise filter on */
#define _01_SAU_RXD0_FILTER_ON                   (0x01U)

/*
    Format of Serial Status Register mn (SSRmn)
*/
/* Communication status indication flag of channel n (TSFmn) */

/* communication is under execution */
#define _0040_SAU_UNDER_EXECUTE                  (0x0040U)

/* Buffer register status indication flag of channel n (BFFmn) */

/* valid data is stored in the SDRmn register */
#define _0020_SAU_VALID_STORED                   (0x0020U)

/* Framing error detection flag of channel n (FEFmn) */

/* a framing error occurs during UART reception */
#define _0004_SAU_FRAM_ERROR                     (0x0004U)

/* Parity error detection flag of channel n (PEFmn) */

/* a parity error occurs or ACK is not detected */
#define _0002_SAU_PARITY_ERROR                   (0x0002U)

/* Overrun error detection flag of channel n (OVFmn) */

/* an overrun error occurs */
#define _0001_SAU_OVERRUN_ERROR                  (0x0001U)

/*
    Serial Channel Start Register m (SSm)
*/
/* Operation start trigger of channel 0 (SSm0) */

/* no trigger operation */
#define _0000_SAU_CH0_START_TRG_OFF              (0x0000U)
/* sets SEm0 to 1 and enters the communication wait status */
#define _0001_SAU_CH0_START_TRG_ON               (0x0001U)

/* Operation start trigger of channel 1 (SSm1) */

/* no trigger operation */
#define _0000_SAU_CH1_START_TRG_OFF              (0x0000U)
/* sets SEm1 to 1 and enters the communication wait status */
#define _0002_SAU_CH1_START_TRG_ON               (0x0002U)

/*
    Serial Channel Stop Register m (STm)
*/
/* Operation stop trigger of channel 0 (STm0) */
#define _0000_SAU_CH0_STOP_TRG_OFF               (0x0000U) /* no trigger operation */
#define _0001_SAU_CH0_STOP_TRG_ON                (0x0001U) /* operation is stopped (stop trigger is generated) */
/* Operation stop trigger of channel 1 (STm1) */
#define _0000_SAU_CH1_STOP_TRG_OFF               (0x0000U) /* no trigger operation */
#define _0002_SAU_CH1_STOP_TRG_ON                (0x0002U) /* operation is stopped (stop trigger is generated) */

/*
    Format of Serial Flag Clear Trigger Register mn (SIRmn)
*/
/* Clear trigger of overrun error flag of channel n (OVCTmn) */
#define _0001_SAU_SIRMN_OVCTMN                   (0x0001U)
/* Clear trigger of parity error flag of channel n (PECTmn) */
#define _0002_SAU_SIRMN_PECTMN                   (0x0002U)
/* Clear trigger of framing error of channel n (FECTMN) */
#define _0004_SAU_SIRMN_FECTMN                   (0x0004U)

/*
    Serial Output Enable Register m (SOEm)
*/
/* Serial output enable/disable of channel 0 (SOEm0) */

/* stops output by serial communication operation */
#define _0001_SAU_CH0_OUTPUT_ENABLE              (0x0001U)
/* enables output by serial communication operation */
#define _0000_SAU_CH0_OUTPUT_DISABLE             (0x0000U)


/* Serial output enable/disable of channel 1 (SOEm1) */

/* stops output by serial communication operation */
#define _0002_SAU_CH1_OUTPUT_ENABLE              (0x0002U)
/* enables output by serial communication operation */
#define _0000_SAU_CH1_OUTPUT_DISABLE             (0x0000U)

/*
    Serial Output Register m (SOm)
*/
/* Serial data output of channel 0 (SOm0) */

/* serial data output value is "0" */
#define _0000_SAU_CH0_DATA_OUTPUT_0              (0x0000U)
/* serial data output value is "1" */
#define _0001_SAU_CH0_DATA_OUTPUT_1              (0x0001U)

/* Serial data output of channel 1 (SOm1) */

/* serial data output value is "0" */
#define _0000_SAU_CH1_DATA_OUTPUT_0              (0x0000U)
/* serial data output value is "1" */
#define _0002_SAU_CH1_DATA_OUTPUT_1              (0x0002U)

/* Serial clock output of channel 0 (CKOm0) */

/* serial clock output value is "0" */
#define _0000_SAU_CH0_CLOCK_OUTPUT_0             (0x0000U)
/* serial clock output value is "1" */
#define _0100_SAU_CH0_CLOCK_OUTPUT_1             (0x0100U)

/* Serial clock output of channel 1 (CKOm1) */

/* serial clock output value is "0" */
#define _0000_SAU_CH1_CLOCK_OUTPUT_0             (0x0000U)
/* serial clock output value is "1" */
#define _0200_SAU_CH1_CLOCK_OUTPUT_1             (0x0200U)

/* SAU Standby Control Register m (SSCm) */

/* SAU Standby Wakeup Control Bit (SWC) */

/* disable start function from STOP state of chip */
#define _0000_SAU_CH0_SNOOZE_OFF                 (0x0000U)
/* enable start function from STOP state of chip */
#define _0001_SAU_CH0_SNOOZE_ON                  (0x0001U)


/*
    Peripheral enable register 0 (PER0)
*/
/* Control of IICA input clock (IICA0EN) */
/* stops supply of input clock */
#define _00_IICA_CLOCK_STOP                      (0x00U)
/* supplies input clock */
#define _10_IICA_CLOCK_SUPPLY                    (0x10U)

/*
    IICA Control Register (IICCTLn0)
*/
/* IIC operation enable (IICEn) */
/* stop operation */
#define _00_IICA_OPERATION_DISABLE               (0x00U)
/* enable operation */
#define _80_IICA_OPERATION_ENABLE                (0x80U)

/* Exit from communications (LRELn) */
/* normal operation */
#define _00_IICA_COMMUNICATION_NORMAL            (0x00U)
/* exit from current communication */
#define _40_IICA_COMMUNICATION_EXIT              (0x40U)

/* Wait cancellation (WRELn) */
/* do not cancel wait */
#define _00_IICA_WAIT_NOTCANCEL                  (0x00U)
/* cancel wait */
#define _20_IICA_WAIT_CANCEL                     (0x20U)

/* Generation of interrupt when stop condition (SPIEn) */
/* disable */
#define _00_IICA_STOPINT_DISABLE                 (0x00U)
/* enable */
#define _10_IICA_STOPINT_ENABLE                  (0x10U)

/* Wait and interrupt generation (WTIMn) */
/* generated at the eighth clock's falling edge */
#define _00_IICA_WAITINT_CLK8FALLING             (0x00U)

/* generated at the ninth clock's falling edge */
#define _08_IICA_WAITINT_CLK9FALLING             (0x08U)

/* Acknowledgement control (ACKEn) */
/* disable acknowledgement */
#define _00_IICA_ACK_DISABLE                     (0x00U)
/* enable acknowledgement */
#define _04_IICA_ACK_ENABLE                      (0x04U)

/* Start condition trigger (STTn) */
/* do not generate start condition */
#define _00_IICA_START_NOTGENERATE               (0x00U)
/* generate start condition */
#define _02_IICA_START_GENERATE                  (0x02U)

/* Stop condition trigger (SPTn) */
/* do not generate stop condition */
#define _00_IICA_STOP_NOTGENERATE                (0x00U)
/* generate stop condition */
#define _01_IICA_STOP_GENERATE                   (0x01U)

/* IICA Status Register (IICSn) */

/* Master device status (MSTSn) */
/* slave device status or communication standby status */
#define _00_IICA_STATUS_NOTMASTER                (0x00U)
/* master device communication status */
#define _80_IICA_STATUS_MASTER                   (0x80U)

/* Detection of arbitration loss (ALDn) */
/* arbitration win or no arbitration */
#define _00_IICA_ARBITRATION_NO                  (0x00U)
/* arbitration loss */
#define _40_IICA_ARBITRATION_LOSS                (0x40U)

/* Detection of extension code reception (EXCn) */
/* extension code not received */
#define _00_IICA_EXTCODE_NOT                     (0x00U)
/* extension code received */
#define _20_IICA_EXTCODE_RECEIVED                (0x20U)

/* Detection of matching addresses (COIn) */
/* addresses do not match */
#define _00_IICA_ADDRESS_NOTMATCH                (0x00U)
/* addresses match */
#define _10_IICA_ADDRESS_MATCH                   (0x10U)
/* Detection of transmit/receive status (TRCn) */
/* receive status */
#define _00_IICA_STATUS_RECEIVE                  (0x00U)
/* transmit status */
#define _08_IICA_STATUS_TRANSMIT                 (0x08U)

/* Detection of acknowledge signal (ACKDn) */

/* ACK signal was not detected */
#define _00_IICA_ACK_NOTDETECTED                 (0x00U)
/* ACK signal was detected */
#define _04_IICA_ACK_DETECTED                    (0x04U)
/* Detection of start condition (STDn) */
/* start condition not detected */
#define _00_IICA_START_NOTDETECTED               (0x00U)
/* start condition detected */
#define _02_IICA_START_DETECTED                  (0x02U)
/* Detection of stop condition (SPDn) */
/* stop condition not detected */
#define _00_IICA_STOP_NOTDETECTED                (0x00U)
/* stop condition detected */
#define _01_IICA_STOP_DETECTED                   (0x01U)

/*
    IICA Flag Register (IICFn)
*/
/* STT clear flag (STCFn) */
/* generate start condition */
#define _00_IICA_STARTFLAG_GENERATE              (0x00U)
/* start condition generation unsuccessful */
#define _80_IICA_STARTFLAG_UNSUCCESSFUL          (0x80U)

/* IIC bus status flag (IICBSYn) */
/* bus release status */
#define _00_IICA_BUS_RELEASE                     (0x00U)
/* bus communication status */
#define _40_IICA_BUS_COMMUNICATION               (0x40U)
/* Initial start enable trigger (STCENn) */
/* generation of a start condition upon detecting a stop condition */
#define _00_IICA_START_WITHSTOP                  (0x00U)
/* generation of a start condition without detection of a stop condition */
#define _02_IICA_START_WITHOUTSTOP               (0x02U)
/* Communication reservation function disable bit (IICRSVn) */
/* enable communication reservation */

#define _00_IICA_RESERVATION_ENABLE              (0x00U)
/* disable communication reservation */
#define _01_IICA_RESERVATION_DISABLE             (0x01U)

/*
    IICA Control Register 1 (IICCTLn1)
*/
/* Control of address match wakeup (WUPn) */
/* stop address match wakeup function in STOP mode */
#define _00_IICA_WAKEUP_STOP                     (0x00U)
/* enable address match wakeup function in STOP mode */
#define _80_IICA_WAKEUP_ENABLE                   (0x80U)

/* Detection of SCL0 pin level (CLDn) */
/* detect clock line at low level */
#define _00_IICA_SCL_LOW                         (0x00U)
/* detect clock line at high level */
#define _20_IICA_SCL_HIGH                        (0x20U)

/* Detection of SDA0 pin level (DADn) */
/* detect data line at low level */
#define _00_IICA_SDA_LOW                         (0x00U)
/* detect data line at high level */
#define _10_IICA_SDA_HIGH                        (0x10U)

/* Operation mode switching (SMCn) */
/* operates in standard mode */
#define _00_IICA_MODE_STANDARD                   (0x00U)
/* operates in high-speed mode */
#define _08_IICA_MODE_HIGHSPEED                  (0x08U)

/* Digital filter operation control (DFCn) */
/* digital filter off */
#define _00_IICA_FILTER_OFF                      (0x00U)
/* digital filter on */
#define _04_IICA_FILTER_ON                       (0x04U)
/* Operation of clock dividing frequency permission (PRSn) */
/* clock of dividing frequency operation (fCLK) */
#define _00_IICA_fCLK                            (0x00U)
/* 2 clock of dividing frequency operation (fCLK/2) */
#define _01_IICA_fCLK_HALF                       (0x01U)

/* IICA used flag */
#define _80_IICA_ADDRESS_COMPLETE                (0x80U)
#define _00_IICA_MASTER_FLAG_CLEAR               (0x00U)

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _9A00_UART0_RECEIVE_DIVISOR              (0x9A00U)
#define _9A00_UART0_TRANSMIT_DIVISOR             (0x9A00U)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_SAU0_Create(void);
void R_UART0_Create(void);
void R_UART0_Start(void);
void R_UART0_Stop(void);
MD_STATUS R_UART0_Send(uint8_t * const tx_buf, uint16_t tx_num);
static void r_uart0_callback_receiveend(void);

/***********************************************************************************************************************
Definitions
***********************************************************************************************************************/
/* Define the RAM protect area size in bytes */
#define RAM_PROTECT_SIZE            128U
/* Define the ADC buffer size */
#define ADC_BUFFER_SIZE             32U
/* Only the first 8 bytes of the protected RAM area are written to and read from */
#define RAM_PROTECT_READ            8u
/* Delay added between ADC data bytes sent to the GUI in the CRC and DMAC responses */
#define TRANSMIT_DELAY              0x1FFU

/* Used to the GUI command, whether a peripheral function is requested or not */
#define ENABLE_FUNC                 (uint8_t)0x01
#define DISABLE_FUNC                (uint8_t)0x02
#define SET_LIMITS                  (uint8_t)0x03

#define STOP_MODE_ENABLE            (uint8_t)0x01
#define HALT_MODE_ENABLE            (uint8_t)0x02

/* Verifies whether the LCD is to remain on during STOP mode */
#define ENABLE_LCD_STBY             (uint8_t)0x80

/* Used for checking the bit settings of the GUI's command */
#define CHECK_BITS                  0x0Fu

/* Command to exit release mode */
#define EXIT_STANDBY                (uint8_t)0x03

#define DISABLE_GUARD               (uint8_t)0x00
#define SFR_GUARD_ON                (uint8_t)0x01
#define RAM_GUARD_ON                (uint8_t)0x02

#define CPU_TEMP                    0x32U

#define INT_REF_ADC_ITERATIONS      5U

/***********************************************************************************************************************
Typedef Definitions
***********************************************************************************************************************/
/*typedef struct _Comms_Buffer
{
     Read Pointer
    uint8_t rdPtr;
    
     Write Pointer
    uint8_t wrPtr;
    
     The Buffer
    volatile uint8_t buffer[RX_BUFF_SIZE];
}
 Declare a structure of type _Comms_Buffer
Comms_Buffer;*/


/***********************************************************************************************************************
* Exported Global Variables and Functions
***********************************************************************************************************************/
/* UART0 Tx buffer */
//extern uint8_t g_tx_buff[16];
/* uart0 send buffer address */
//extern volatile uint8_t * gp_uart0_tx_address;
/* uart0 send data number */
//extern volatile uint16_t  g_uart0_tx_count;
/* uart0 receive buffer address */
//extern volatile uint8_t * gp_uart0_rx_address;
/* uart0 receive data number */
//extern volatile uint16_t  g_uart0_rx_count;
/* uart0 receive data length */
//extern volatile uint16_t  g_uart0_rx_length;

/* Function prototypes used in r_cg_serial_user.c file*/
void R_UART0_Create(void);
void R_SAU0_Create(void);

#endif
