	//*****************************************************************************
	// main_checker_board.c
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
	tRectangle sRect;   //used for the box
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
    // MY DRAWING DOWN HERE of checker_board
    // -------------------------------------------------------------------------------------


    
	

    int blocks_x = 8;
    int blocks_y = 8;

    int block_edge_size = 14;

    int i; 
    int j;

    bool white = true;

    //drawing the grid

    for(i = 0 ; i<blocks_x ; i = i+1){
        
        for(j = 0 ; j<blocks_y ; j = j+1 ){

            //drawing one box "|_|"
            //I put 41,32,55,47 to make the checkerboard not start in 0,0, to make it prettier :Ds
            sRect.i16XMin = 41+(i*block_edge_size);
	        sRect.i16YMin = 32+(j*block_edge_size);
	        sRect.i16XMax = 55+(i*block_edge_size);
	        sRect.i16YMax = 47+(j*block_edge_size);

            if(white){
                GrContextForegroundSet(&sContext, ClrWhite);  //paint the rectangle of white color
            }else{
                GrContextForegroundSet(&sContext, ClrBlack);  //paint the rectangle of black color
            }

            white = !white;
	        

            GrRectFill(&sContext, &sRect);
        }

        white = !white;

    }

    
	//
	// Flush any cached drawing operations.
	//
	GrFlush(&sContext);

	//
	// We are finished. Hang around doing nothing.
	//
	
	while(1)
	{
    //wait some time
	ROM_SysCtlDelay(ROM_SysCtlClockGet()/2);

	}
}

