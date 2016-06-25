/*
    FreeRTOS V7.0.1 - Copyright (C) 2011 Real Time Engineers Ltd.

	Modified by Dag Ågren, Åbo Akademi University - Dept. of Information Technologies:
	implemented support for UARTs on the OMAP4.

	FreeRTOS supports many tools and architectures. V7.0.0 is sponsored by:
	Atollic AB - Atollic provides professional embedded systems development
	tools for C/C++ development, code analysis and test automation.
	See http://www.atollic.com


    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/* UART Driver for the OMAP4. */

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "semphr.h"

#define REG8(address) (*(volatile unsigned char *)(address))
#define REG32(address) (*(volatile unsigned int *)(address))

#define OMAP44XX_L4_PER 0x48000000
#define UART0_BASE (OMAP44XX_L4_PER+0x6a000) // OMAP4460, UART1 in data sheet
#define UART1_BASE (OMAP44XX_L4_PER+0x6c000) // OMAP4460, UART2 in data sheet
#define UART2_BASE (OMAP44XX_L4_PER+0x20000) // OMAP4460, UART3 in data sheet
#define UART3_BASE (OMAP44XX_L4_PER+0x6e000) // OMAP4460, UART4 in data sheet

#define UART_RBR(base) REG8((base)+0x00)
#define UART_IER(base) REG8((base)+0x04)
#define UART_FCR(base) REG8((base)+0x08)
#define UART_LCR(base) REG8((base)+0x0c)
#define UART_MCR(base) REG8((base)+0x10)
#define UART_LSR(base) REG8((base)+0x14)
#define UART_MSR(base) REG8((base)+0x18)
#define UART_SCR(base) REG8((base)+0x1c)
#define UART_MDR1(base) REG8((base)+0x20)

#if configPLATFORM == 3

//#define UART_CLK 3686400

void vUARTInitialise(unsigned long ulUARTPeripheral, unsigned long ulBaud, unsigned long ulQueueSize )
{
/*	unsigned long base;
	switch(ulUARTPeripheral)
	{
		case 0: base=UART0_BASE; break;
		case 1: base=UART1_BASE; break;
		case 2: base=UART2_BASE; break;
		case 3: base=UART3_BASE; break;
		default: return;
	}*/

	/* First Disable the Peripheral. */
//	*UARTCR(ulBase) = 0UL;

	/* Configure the Peripheral. */
//	*UARTIBRD(ulBase) = UART_CLK / ( 16 * ulBaud );
//	*UARTFBRD(ulBase) = UART_CLK % ( 16 * ulBaud );
//	*UARTLCR_H(ulBase) = ( 3 << 5 ) | ( 1 << 4 );

	/* Configure the Interrupts. */
//	*UARTIFLS(ulBase) = ( 0 << 3 ) | ( 0 << 0 );
//	*UARTICR(ulBase) = 0xFFFF;	/* Clear all Iterrupts. */

	/* Finally enable the peripheral. */
//	*UARTCR(ulBase) = ( 1 << 9 ) | ( 1 << 8 ) | /* Loopback Enable ( 1 << 7 ) | */ ( 1 << 0 );
}
/*----------------------------------------------------------------------------*/

portBASE_TYPE xUARTSendCharacter( unsigned long ulUARTPeripheral, signed char cChar, portTickType xDelay )
{
	unsigned long base;
	switch(ulUARTPeripheral)
	{
		case 0: base=UART0_BASE; break;
		case 1: base=UART1_BASE; break;
		case 2: base=UART2_BASE; break;
		case 3: base=UART3_BASE; break;
		default: return pdFALSE;
	}

	while((UART_LSR(base)&0x20)==0);
	UART_RBR(base)=cChar;

	return pdTRUE;
}
/*----------------------------------------------------------------------------*/

portBASE_TYPE xUARTReceiveCharacter( unsigned long ulUARTPeripheral, signed char *pcChar, portTickType xDelay )
{
	unsigned long base;
	switch(ulUARTPeripheral)
	{
		case 0: base=UART0_BASE; break;
		case 1: base=UART1_BASE; break;
		case 2: base=UART2_BASE; break;
		case 3: base=UART3_BASE; break;
		default: return pdFALSE;
	}

	if((UART_LSR(base)&0x01)==0) return pdFALSE;

	*pcChar=UART_RBR(base);
	return pdTRUE;
}

#endif /* configPLATFORM == 3 */

