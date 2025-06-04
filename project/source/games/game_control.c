/*
 * game_control.c
 *
 *  Created on: Apr 10, 2025
 *      Author: yalukaiwo
 */

#include "game_control.h"
#include "gps_location.game.h"
#include "stdio.h"

game_controller_t gameControl;

game_controller_t * initGameControl() {
	gameControl.currentGame = TUTORIAL;
	gameControl.gameFailFlag = false;
	gameControl.gameSuccessFlag = false;
}

game_controller_t * getGameControl() {
	return &gameControl;
}

void checkGameStatus() {
	if (gameControl.gameFailFlag) // If the game fail flag is raised
	{
		// Display fail message

		gameControl.gameFailFlag = false; // Disable the flag
	    gameControl.currentGame = TUTORIAL; // Reset the game
	}

	if (gameControl.gameSuccessFlag) // If the game success flag is raised
	{
		// Display success message and open the box

	    gameControl.gameSuccessFlag = false; // Disable the flag

	    if (gameControl.currentGame == PIN)
	    {
	    	// Success, open the box and display a success message

	    	printf("GAME WON!");

	    	gameControl.currentGame = TUTORIAL; // Reset the game
	    }
	    else
	    {
	    	gameControl.currentGame++;
	    }
	}
}
