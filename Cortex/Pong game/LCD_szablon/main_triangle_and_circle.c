	//*****************************************************************************
	// main_triangle_and_circle.c - Triangle and circle
	//
	// Gines Diaz
	//
	// 
	//*****************************************************************************

	#include <stdint.h>
	#include <stdbool.h>
	#include "inc/hw_memmap.h"
	#include "driverlib/fpu.h"
	#include "driverlib/sysctl.h"
	#include "driverlib/rom.h"
	#include "driverlib/pin_map.h"
	#include "driverlib/uart.h"
    #include "grlib/grlib.h"
	#include "drivers/ili9341_240x320x262K.h"
	#include "utils/uartstdio.h"
	#include "driverlib/gpio.h"

	
	//*****************************************************************************
	//
	// Print some text to the display.
	//
	//***********************************************
	int
	main(void)
	{
	tContext sContext;
	tRectangle sRect;

	//
	// Enable lazy stacking for interrupt handlers. This allows floating-point
	// instructions to be used within interrupt handlers, but at the expense of
	// extra stack usage.
	//
	ROM_FPULazyStackingEnable();
	//
	// Set the clocking to run directly from the crystal.
	//
	ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

	//
	// Initialize the display driver.
	//
	ILI9341_240x320x262K_Init();
	//
	// Initialize the graphics context.
	//
	GrContextInit(&sContext, &g_sILI9341_240x320x262K);

    //_____________________________________________________________
    // my code down below 
	//_____________________________________________________________
    
	//left string draw
	GrContextFontSet(&sContext, g_psFontCm12);

	GrStringDraw(&sContext,
	"Hello",
	-1,
	108,
	GrContextDpyHeightGet(&sContext) -30,
	0);

	//right string draw
	GrContextFontSet(&sContext, g_psFontCm20b);

	GrStringDraw(&sContext,
	"World",
	-1,
	212,
	GrContextDpyHeightGet(&sContext) -30,
	0);

    //drawing first line "\"
    GrLineDraw(&sContext,
    160,
    60,
    212,
    150);

	//drawing horizontal line "_"
    GrLineDrawH(&sContext,
	212,
	108,
	150);

	//drawing first line "/"
	GrLineDraw(&sContext,
	108,
	150,
	160,
	60);

	GrContextForegroundSet(&sContext, ClrMediumAquamarine);

	//drawing circle "O"
	GrCircleDraw(&sContext,
	160,
	120,
	60);


	//_____________________________________________________________
	//
	// Flush any cached drawing operations.
	//
	GrFlush(&sContext);

	//
	// We are finished. Hang around doing nothing.
	//
	while(1)
	{
	ROM_SysCtlDelay(ROM_SysCtlClockGet()/2);
	}
}

