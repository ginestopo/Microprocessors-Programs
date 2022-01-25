	//*****************************************************************************
	// main_christmast_tree.c 
	//
	// Gines Diaz
	//
	// This is part of revision 1.0 of the EK-LM4F232 Firmware Package.
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
	tRectangle sRect;   //used for the log of the tree
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



	// -------------------------------------------------------------------------------------
    // MY DRAWING DOWN HERE of christmast tree
    // -------------------------------------------------------------------------------------

    //drawing "/"
    // GrLineDraw(&sContext,
    // 160,
    // 36,
    // 111,
    // 166);

    //drawing "\"
    // GrLineDraw(&sContext,
    // 160,
    // 36,
    // 213,
    // 166);

    //drawing "_"
    // GrLineDraw(&sContext,
    // 111,
    // 166,
    // 213,
    // 166);

    //drawing the GREEN tree ( no snow :( )
    GrContextForegroundSet(&sContext, ClrGreen);  

    int x1 = 162;
    int y = 42;
    int x2 = 163;


    //CREATE A LOOP TO CREATE GREEN TREE
    
    int i;

    for(i = 1 ; i < 130 ; i++){
        GrLineDraw(&sContext,
        x1,
        y,
        x2,
        y);

        x1 = x1-1;
        x2 = x2+1;
        y = y+2;
    }


    //drawing log of the tree "|_|"
	sRect.i16XMin = 149;
	sRect.i16YMin = 166;
	sRect.i16XMax = 177;
	sRect.i16YMax = 202;

	GrContextForegroundSet(&sContext, ClrSaddleBrown);  //paint the rectangle of brown color

    GrRectFill(&sContext, &sRect);

    //drawing three balls 
    GrCircleFill(&sContext,
    173,
    92,
    4);

    GrCircleFill(&sContext,
    137,
    125,
    6);

    GrCircleFill(&sContext,
    178,
    139,
    8);

	
	
	//
	// Flush any cached drawing operations.
	//
	GrFlush(&sContext);

	//
	// We are finished. Hang around doing nothing.
	//
	
	while(1)
	{
    GrContextForegroundSet(&sContext, ClrSaddleBrown);

    //drawing three balls lighting
    GrCircleFill(&sContext,
    173,
    92,
    4);

    GrCircleFill(&sContext,
    137,
    125,
    6);

    GrCircleFill(&sContext,
    178,
    139,
    8);

    //___________________________________________________

    //wait some time
	ROM_SysCtlDelay(ROM_SysCtlClockGet()/2);


    GrContextForegroundSet(&sContext, ClrRoyalBlue );

    //drawing three balls lighting
    GrCircleFill(&sContext,
    173,
    92,
    4);

    GrCircleFill(&sContext,
    137,
    125,
    6);

    GrCircleFill(&sContext,
    178,
    139,
    8);

    //___________________________________________________

    //wait some time
	ROM_SysCtlDelay(ROM_SysCtlClockGet()/2);

    GrContextForegroundSet(&sContext, ClrYellow);

    //drawing three balls lighting
    GrCircleFill(&sContext,
    173,
    92,
    4);

    GrCircleFill(&sContext,
    137,
    125,
    6);

    GrCircleFill(&sContext,
    178,
    139,
    8);




    //wait some time
	ROM_SysCtlDelay(ROM_SysCtlClockGet()/2);

	}
}

