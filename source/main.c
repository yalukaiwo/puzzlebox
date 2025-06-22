/*! ***************************************************************************
 *
 * \brief     Main application
 * \file      main.c
 * \author    Hugo Arends
 * \date      February 2024
 *
 * \see       NXP. (2024). MCX A153, A152, A143, A142 Reference Manual. Rev. 4,
 *            01/2024. From:
 *            https://www.nxp.com/docs/en/reference-manual/MCXAP64M96FS3RM.pdf
 *
 * \copyright 2024 HAN University of Applied Sciences. All Rights Reserved.
 *            \n\n
 *            Permission is hereby granted, free of charge, to any person
 *            obtaining a copy of this software and associated documentation
 *            files (the "Software"), to deal in the Software without
 *            restriction, including without limitation the rights to use,
 *            copy, modify, merge, publish, distribute, sublicense, and/or sell
 *            copies of the Software, and to permit persons to whom the
 *            Software is furnished to do so, subject to the following
 *            conditions:
 *            \n\n
 *            The above copyright notice and this permission notice shall be
 *            included in all copies or substantial portions of the Software.
 *            \n\n
 *            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *            OTHER DEALINGS IN THE SOFTWARE.
 *
 *****************************************************************************/
#include <MCXA153.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "lpuart0_interrupt.h"
#include "lpuart2_interrupt.h"
#include "lpi2c0_controller_interrupt.h"

#include "utils/GPS.h"
#include "utils/SD.h"
#include "utils/Logger.h"
#include "utils/Millis.h"
#include "utils/Leds.h"
#include "utils/Buttons.h"
#include "utils/Keypad.h"
#include "utils/Lock.h"
#include <utils/Buzzer.h>
#include "utils/LCD.h"

#include "games/game_control.h"
#include "games/gps_location.game.h"
#include "games/gps_proximity.game.h"
#include "games/memory.game.h"

#include <MCXA153.h>


// -----------------------------------------------------------------------------
// Local type definitions
// -----------------------------------------------------------------------------
#ifdef DEBUG
#define TARGETSTR "Debug"
#else
#define TARGETSTR "Release"
#endif

// -----------------------------------------------------------------------------
// Local function prototypes
// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------
// Local variables
// -----------------------------------------------------------------------------

static volatile long prevMillis = 0;


// -----------------------------------------------------------------------------
// Main application
// -----------------------------------------------------------------------------
int main(void)
{

	Millis_init();
	lpuart0_init(115200);
	lpuart2_init(9600);
	lpi2c0_controller_init();
	SD_Init();
    Buttons_init();
    Lock_init();
    Leds_init();
    Keypad_init();
    Buzzer_init();
    LCD_init();

    game_controller_t *gameControl = initGameControl();

//    initGPSLocationGame();
//    initGPSProximityGame();
//    initMemoryGame();

    directions_t *directions;

    __enable_irq();

    while (1) {
    	GPS_updateData();


    	LCD_set_cursor(0,0);
    	LCD_send_string("hello world");


    }

//    while(1)
//    {
//    	long currentMillis = millis();
//    	GPS_updateData();
//    	directions = GPS_getCurrentDirections();
//
//    	checkGameStatus();
//
//    	if (currentMillis - prevMillis >= 60000) {
//    		Logger_updateData();
//    		prevMillis = currentMillis;
//    	}
//
//    	switch (gameControl->currentGame) {
//    	case TUTORIAL:
//    		gameControl->gameSuccessFlag = TRUE;
//    		break;
//    	case LOCATION:
//    		gameControl->gameSuccessFlag = TRUE;
//    		break;
//    	case MEMORY:
//    		memoryGame();
//    		break;
//    	case QUIZ:
//    		gameControl->gameSuccessFlag = TRUE;
//    		break;
//    	case PROXIMITY:
//    		gameControl->gameSuccessFlag = TRUE;
//    		break;
//    	case PIN:
//    		gameControl->gameSuccessFlag = TRUE;
//    		break;
//    	case  VICTORY:
//    		gameControl->gameSuccessFlag = TRUE;
//    		break;
//    	default:
//    		gameControl->gameFailFlag = TRUE;
//    		break;
//    	}
//
//    }


}



// -----------------------------------------------------------------------------
// Local function implementation
// -----------------------------------------------------------------------------



