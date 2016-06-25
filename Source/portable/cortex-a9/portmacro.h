
/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/


#ifndef PORTMACRO_H
#define PORTMACRO_H

#include "FreeRTOSConfig.h"

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

typedef signed char     int8_t;
typedef short int       int16_t;

/* Type definitions. */
#define portCHAR        char
#define portFLOAT       float
#define portDOUBLE      double
#define portLONG        long
#define portSHORT       short
#define portSTACK_TYPE  uint32_t
#define portBASE_TYPE   portLONG

typedef portSTACK_TYPE StackType_t;
typedef int32_t BaseType_t;
typedef uint32_t UBaseType_t;

#if( configUSE_16_BIT_TICKS == 1 )
    typedef uint16_t TickType_t;
    #define portMAX_DELAY ( TickType_t ) 0xffff
#else
    typedef uint32_t TickType_t;
    #define portMAX_DELAY ( TickType_t ) 0xffffffffUL
#endif
/*-----------------------------------------------------------*/

/* Architecture specifics. */
#define portSTACK_GROWTH            ( -1 )
#define portTICK_PERIOD_MS          ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT          8
//#define portNOP()                   __asm volatile ( "NOP" );
/*-----------------------------------------------------------*/

/* Critical section management. */
extern void vTaskEnterCritical();
extern void vTaskExitCritical();
#define portCRITICAL_NESTING_IN_TCB			1
#define portENTER_CRITICAL()				vTaskEnterCritical()
#define portEXIT_CRITICAL()					vTaskExitCritical()

extern portBASE_TYPE xPortSetInterruptMask(void);
extern void vPortClearInterruptMask(portBASE_TYPE);
#define portSET_INTERRUPT_MASK()				xPortSetInterruptMask()
#define portCLEAR_INTERRUPT_MASK(x)				vPortClearInterruptMask(x)
#define portSET_INTERRUPT_MASK_FROM_ISR()		portSET_INTERRUPT_MASK()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR(x)	portCLEAR_INTERRUPT_MASK(x)
#define portDISABLE_INTERRUPTS()				((void)portSET_INTERRUPT_MASK())
/* #define portENABLE_INTERRUPTS()					portCLEAR_INTERRUPT_MASK(configLOWEST_INTERRUPT_PRIORITY) */
static inline void portENABLE_INTERRUPTS(void)
{
	portCLEAR_INTERRUPT_MASK(configLOWEST_INTERRUPT_PRIORITY);
	__asm__ __volatile__ ( "nop" ); /* Allow the yield SGI time to propagate. */
#if configPLATFORM==3
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
	__asm__ __volatile__ ( "nop" );
#endif
}

/*-----------------------------------------------------------*/

/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters ) void vFunction( void *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters ) void vFunction( void *pvParameters )

#define portNOP()

static inline unsigned long portCORE_ID(void)
{
	unsigned long val;
	__asm(" mrc p15,0,%[val],c0,c0,5\n":[val] "=r" (val)::);
	return val&3;
}

#if configPLATFORM == 0
	/* The System Control Registers. */
	#define portSYSCTRL_ZERO_REG				( ( volatile unsigned long * ) 0x10001000 )		/* realview-pbx-a9 */
	#define portSYSCTRL_ONE_REG					( ( volatile unsigned long * ) 0x1001A000 )		/* realview-pbx-a9 */
	#define portSYSCTRL_ZERO_TIMER0_ENABLE		( 0x00018000 )

	/* Peripheral Base. */
	#define portPERIPHBASE							( 0x1F000000UL )	/* realview-pbx-a9 */
	#define portGIC_PRIVATE_BASE					( portPERIPHBASE + 0x100UL )
	#define portGIC_DISTRIBUTOR_BASE				( portPERIPHBASE + 0x1000UL )
	#define portGIC2_BASE							( 0x1DFFFF00UL )	/* realview-pbx-a9 */
	#define portGIC2_DISTRIBUTOR_BASE				( 0x1E000000UL )	/* realview-pbx-a9 */
	#define portEXCEPTION_VECTORS_BASE				( 0x0UL )
	#define portMAX_VECTORS							( 64UL )
#elif configPLATFORM == 1
	/* Peripheral Base. */
	#define portPERIPHBASE							( 0x50040000UL )	/* nVidia Tegra 2 */
	#define portGIC_PRIVATE_BASE					( portPERIPHBASE + 0x100UL )
	#define portGIC_PRIMARY_BASE					( 0x60004000UL )	/* nVidia Tegra 2 */
	#define portGIC_SECONDARY_BASE					( 0x60004100UL )	/* nVidia Tegra 2 */
	#define portGIC_TERTIARY_BASE					( 0x60004200UL )	/* nVidia Tegra 2 */
	#define portGIC_QUATERNARY_BASE					( 0x60004300UL )	/* nVidia Tegra 2 */
	#define portGIC_DISTRIBUTOR_BASE				( portPERIPHBASE + 0x1000UL )
	#define portEXCEPTION_VECTORS_BASE				( 0x00000000UL )	/* nVidia Tegra 2 */
	#define portMAX_VECTORS							( 160UL )
#elif configPLATFORM == 2
	/* Peripheral Base. */
	#define portPERIPHBASE							( 0x1E000000 )		/* vexpress-a9 */
	#define portGIC_PRIVATE_BASE					( portPERIPHBASE + 0x100UL )
	#define portGIC_DISTRIBUTOR_BASE				( portPERIPHBASE + 0x1000UL )
//	#define portEXCEPTION_VECTORS_BASE				( 0x0UL )
	#define portEXCEPTION_VECTORS_BASE				( portCORE_ID()*0x1000000 )
	#define portMAX_VECTORS							( 32UL )
#elif configPLATFORM == 3
	/* Peripheral Base. */
	#define portPERIPHBASE							( 0x48240000 )		/* pandaboard */
	#define portGIC_PRIVATE_BASE					( portPERIPHBASE + 0x100UL )
	#define portGIC_DISTRIBUTOR_BASE				( portPERIPHBASE + 0x1000UL )
	#define portEXCEPTION_VECTORS_BASE				( 0x80000000+portCORE_ID()*0x20000000 )
	#define portMAX_VECTORS							( 32UL )
#endif

/* Snoop Control Unit Processor Registers. */
#define portSCU_BASE						( portPERIPHBASE + 0x00UL )
#define portSCU_CONTROL						( ( volatile unsigned long * ) ( portSCU_BASE + 0x00UL ) )
#define portSCU_CONFIGURATION				( ( volatile unsigned long * ) ( portSCU_BASE + 0x04UL ) )

/* GIC Processor Registers. */
#define portGIC_ICCICR(x)					( ((unsigned long)(x)) + 0x00UL )
#define portGIC_ICCPMR(x)					( ((unsigned long)(x)) + 0x04UL )
#define portGIC_ICCBPR(x)					( ((unsigned long)(x)) + 0x08UL )
#define portGIC_ICCIAR(x)					( ((unsigned long)(x)) + 0x0CUL )
#define portGIC_ICCEOIR(x)					( ((unsigned long)(x)) + 0x10UL )
#define portGIC_ICCRPR(x)					( ((unsigned long)(x)) + 0x14UL )
#define portGIC_ICCHPIR(x)					( ((unsigned long)(x)) + 0x18UL )

/* GIC Distributor Registers. */
#define portGIC_ICDDCR(x)					( ((unsigned long)(x)) + 0x00UL )
#define portGIC_ICDICTR(x)					( ((unsigned long)(x)) + 0x04UL )
#define portGIC_ICDISER_BASE(x)				( ((unsigned long)(x)) + 0x100UL )
#define portGIC_ICDICER_BASE(x)				( ((unsigned long)(x)) + 0x180UL )
#define portGIC_ICDISPR_BASE(x)				( ((unsigned long)(x)) + 0x200UL )
#define portGIC_ICDICPR_BASE(x)				( ((unsigned long)(x)) + 0x280UL )
#define portGIC_ICDABR_BASE(x)				( ((unsigned long)(x)) + 0x300UL )
#define portGIC_ICDIPR_BASE(x)				( ((unsigned long)(x)) + 0x400UL )
#define portGIC_ICDIPTR_BASE(x)				( ((unsigned long)(x)) + 0x800UL )
#define portGIC_ICDICR_BASE(x)				( ((unsigned long)(x)) + 0xC00UL )
#define portGIC_ICDPPIS(x)					( ((unsigned long)(x)) + 0xD00UL )
#define portGIC_ICDSPIS_BASE(x)				( ((unsigned long)(x)) + 0xD04UL )
#define portGIC_ICDSGIR(x)					( ((unsigned long)(x)) + 0xF00UL )
#define portGIC_ICDCPENDGIR(x)				( ((unsigned long)(x)) + 0xF10UL )
#define portGIC_ICDSPENDGIR(x)				( ((unsigned long)(x)) + 0xF20UL )

/* Macros to access the GIC. */
#define portGIC_WRITE(address,value)		( *( ( unsigned long * volatile )( address ) ) = ( value ) )
#define portGIC_SET(address,value)			( *( ( unsigned long * volatile )( address ) ) |= ( value ) )
#define portGIC_READ(address)				( *( ( unsigned long * volatile )( address ) ) )
#define portGIC_CLEAR(address,value)		( *( ( unsigned long * volatile )( address ) ) &= ~( value ) )

/* GIC Values. */
#define portGIC_CONTROL_ENABLE_INTERRUPTS	( 0x01UL )
#define portGIC_CONTROL_DISABLE_INTERRUPTS	( 0x00UL )
#define portGIC_PRIORITY_MASK_MASK			( 0xF0UL )
#define portGIC_SPURIOUS_VECTOR				( 1023 )
#define portGIC_CPU_INTERRUPT_SOURCE_MASK	( 0x1C00UL )
#define portGIC_VECTOR_MASK					( 0x3FFUL )

/* Private Timers. */
#define portSYSTICK_BASE				( portPERIPHBASE + 0x600 )
#define portSYSTICK_LOAD				( ( volatile unsigned long * ) ( portSYSTICK_BASE + 0x00 ) )
#define portSYSTICK_CONTROL				( ( volatile unsigned long * ) ( portSYSTICK_BASE + 0x08 ) )
#define portSYSTICK_INTERRUPT_STATUS	( ( volatile unsigned long * ) ( portSYSTICK_BASE + 0x0C ) )
#define portSYSTICK_CTRL_ENABLE_PERIODIC_INTERRUPTS			  ( 0x00000007 )
#define portSYSTICK_PRESCALE			( 99 )		/* realview-pbx-a9 */
#define portSYSTICK_VECTOR_ID			( 29 )

/* SGI for Yielding Task. */
#define portSGI_YIELD_VECTOR_ID			( 1 )
#define portSGI_YIELD( xCPUID )			( ( 0 << 24 ) | ( ( 1 << 16 ) << ( xCPUID ) ) | portSGI_YIELD_VECTOR_ID )
/* #define portYIELD()		( ( portGIC_READ( portGIC_ICDISPR_BASE( portGIC_DISTRIBUTOR_BASE ) ) & portSGI_YIELD_VECTOR_ID ) == 0UL ? portGIC_WRITE( portGIC_ICDSGIR( portGIC_DISTRIBUTOR_BASE ), portSGI_YIELD( portCORE_ID() ) ) : (void)portGIC_DISTRIBUTOR_BASE ) */

static inline void portYIELD(void)
{
	if( ( portGIC_READ( portGIC_ICDISPR_BASE( portGIC_DISTRIBUTOR_BASE ) ) & portSGI_YIELD_VECTOR_ID ) == 0UL)
	{
		portGIC_WRITE( portGIC_ICDSGIR( portGIC_DISTRIBUTOR_BASE ), portSGI_YIELD( portCORE_ID() ) );
		__asm__ __volatile__ ( "nop" ); /* Allow the yield SGI time to propagate. */

#if configPLATFORM == 3
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
		__asm__ __volatile__ ( "nop" );
#endif
	}
}
#define portSGI_CLEAR_YIELD( pxDistributorBase, xCPUID )	portGIC_WRITE( portGIC_ICDICPR_BASE( pxDistributorBase ), portSGI_YIELD_VECTOR_ID )
#define portEND_SWITCHING_ISR( xSwitchRequired ) ( (xSwitchRequired) ? portYIELD() : (void)xSwitchRequired )

/* Processor Mode Definitions (CPSR) */
#define portPROCESSOR_MODE_MASK	( ~(0x1FUL) )
#define portUSER_MODE			( 0x10UL )
#define portFIQ_MODE			( 0x11UL )
#define portIRQ_MODE			( 0x12UL )
#define portSVC_MODE			( 0x13UL )
#define portMON_MODE			( 0x16UL )
#define portABT_MODE			( 0x17UL )
#define portUND_MODE			( 0x1BUL )
#define portSYS_MODE			( 0x1FUL )

/* Stack Size definitions for each of the modes. */
#define portFIQ_STACK_SIZE		( 256 )
#define portIRQ_STACK_SIZE		( 256 )
#define portABORT_STACK_SIZE	( 256 )
#define portSVC_STACK_SIZE		( 256 )

#ifdef __cplusplus
}
#endif

#endif /* PORTMACRO_H */

