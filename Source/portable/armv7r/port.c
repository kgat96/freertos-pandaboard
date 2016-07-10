
/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the ARM7 port.
 *
 * Components that can be compiled to either ARM or THUMB mode are
 * contained in this file.  The ISR routines, which can only be compiled
 * to ARM mode are contained in portISR.c.
 *----------------------------------------------------------*/

/* Standard includes. */
#include <stdlib.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

void vPortEnterCritical( void )
{

}

void vPortExitCritical( void )
{

}

BaseType_t xPortStartScheduler( void )
{
    return 0;
}

void vPortEndScheduler( void )
{

}

StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters )
{
    return 0;
}




/*-----------------------------------------------------------*/
