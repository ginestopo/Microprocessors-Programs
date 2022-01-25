	//*****************************************************************************
	// pong_game_gines.c 
	//
	// Gines Diaz Chamorro 2022
	//
	// This is an implementation of a classic pong game
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



	int
	main(void)
	{
	tContext sContext;

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


	//-------------------JOYSTICK INITIALIZATION---------------

	//Initialize peripherical
	SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOB);	//LEFT and UP
	SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOE);	//RIGHT and DOWN

	//
 	// Set all GPIO pins as inputs
 	//
 	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PINS_ALL);
	GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PINS_ALL);


	//-----------------Definition of variables------------------

	//
	// BALL variables
	// 
	const ball_radius = 10;

	const screen_x = 320;
	const screen_y = 240;

	//speed for the ball, this will be added to the position_ball to give impression of movement
	int speed_x = 3;  
	int speed_y = 3;  

	//position_ball vector
	int position_ball_x = 160;  //initial position_ball in the middle of screen
	int position_ball_y = 120;


	//
	//Left pad variables
	// 

	tRectangle pad_left;

	pad_left.i16XMin = 21;
	pad_left.i16YMin = screen_y/2 - 25;
	pad_left.i16XMax = 29;
	pad_left.i16YMax = screen_y/2 + 25;

	//
	//Right pad variables
	// 

	tRectangle pad_right;

	pad_right.i16XMin = screen_x - 21;
	pad_right.i16YMin = screen_y/2 - 25;
	pad_right.i16XMax = screen_x - 29;
	pad_right.i16YMax = screen_y/2 + 25;


	//control variables
	int y_axis = 0;  //up --> y_axis=1 | down --> y_axis=-1 | idle --> y_axis = 0


	//background will be white
	GrContextBackgroundSet(&sContext, ClrWhite);
	//objects will be black
	GrContextBackgroundSet(&sContext, ClrBlack);


	//
	// Flush any cached drawing operations.
	//
	GrFlush(&sContext);

	//
	// Game loop
	//

	while(1)
	{

	//__________________
	//detect inputs
	//__________________
	//temp_var = GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_0);

	y_axis = (GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_0) == 1) ? 1 : 0 ;  //UP
	y_axis = (GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_5) == 1) ? -1 : 0 ; //DOWN	


	//background will be white
	GrContextBackgroundSet(&sContext, ClrWhite);
	//objects will be black
	GrContextForegroundSet(&sContext, ClrBlack);

	//____________________________________________________________________
	// Draw BALL
	//____________________________________________________________________

	//change x direction of ball if we hit a wall or pad                                 v  From here is pad collision logic
	if( (position_ball_x > screen_x-ball_radius) || (position_ball_x < 0+ball_radius) || (  (position_ball_y < pad_right.i16XMax && position_ball_y >  pad_left.i16YMin) && (position_ball_x > pad_right.i16XMax-ball_radius || position_ball_x < pad_left.i16XMax+ball_radius) )){
		speed_x = -speed_x;

		//if the ball hits the player wall (left wall), game over :D
		if(position_ball_x < 0+ball_radius){
			while (true)
			{
				//GAME OVER

				GrContextFontSet(&sContext, g_psFontCm12);

				//GrStringDrawCentered(where to draw, text to write, if we put 2 it will print 2 characters but -1 prints everything, x pos, y pos, )
				GrStringDrawCentered(&sContext,
				"GAME OVER",
				-1,
				screen_x / 2,
				screen_y / 2),
				0);
			}
			
		}
	}

	//change y direction of ball if we hit a wall
	if( (position_ball_y > screen_y) || (position_ball_y < 0)){
		speed_y = -speed_y;
	}

	position_ball_x += speed_x;
	position_ball_y += speed_y;
	
	GrCircleFill(&sContext,
	position_ball_x,
	position_ball_y,
	ball_radius);

	//____________________________________________________________________
	// Draw pad left
	//____________________________________________________________________
	
	//update position
	if(y_axis > 0){
		pad_left.i16YMin = screen_y/2 - 25 - 10;
		pad_left.i16YMax = screen_y/2 + 25 - 10;
	}
	if(y_axis < 0){
		pad_left.i16YMin = screen_y/2 - 25 + 10;
		pad_left.i16YMax = screen_y/2 + 25 + 10;
	}
	
	GrRectFill(&sContext, &pad_left);

	//____________________________________________________________________
	// Draw pad right (ENEMY)
	//____________________________________________________________________

	//update position
	pad_right.i16YMin = position_ball_y - 25;
	pad_right.i16YMax = position_ball_y + 25;
	GrRectFill(&sContext, &pad_right);

	//____________________________________________________________________


	//wait for next game frame
	ROM_SysCtlDelay(ROM_SysCtlClockGet()/20); //adjust wait time for a a more smooth experience


	//____________________________________________________________________
	// Clean previous BALL
	//____________________________________________________________________

	//let's clean the previous drawings for giving the impression of movement
	GrContextForegroundSet(&sContext, ClrWhite);

	GrCircleFill(&sContext,
	position_ball_x,
	position_ball_y,
	ball_radius);

	GrRectFill(&sContext, &pad_left);
	GrRectFill(&sContext, &pad_right);


	}
}

