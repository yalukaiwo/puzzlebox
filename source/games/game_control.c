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
	char currentGame[2];
	SD_Read(GAMECONTROL_FILENAME, currentGame, sizeof(currentGame) / sizeof(char)); // Read current game from memory

	printf("current game read: %s", currentGame);

	switch (currentGame[0]) { // Apply the saved game level
	case '0':
		gameControl.currentGame = TUTORIAL;
		break;
	case '1':
		gameControl.currentGame = LOCATION;
		break;
	case '2':
		gameControl.currentGame = MEMORY;
		break;
	case '3':
		gameControl.currentGame = QUIZ;
		break;
	case '4':
		gameControl.currentGame = PROXIMITY;
		break;
	case '5':
		gameControl.currentGame = PIN;
		break;
	case '6':
		gameControl.currentGame = VICTORY;
		break;
	default:
		gameControl.currentGame = TUTORIAL;
		break;
	}

	gameControl.gameFailFlag = FALSE;
	gameControl.gameSuccessFlag = FALSE;
}

game_controller_t * getGameControl() {
	return &gameControl;
}

void checkGameStatus() {
	if (gameControl.gameFailFlag) // If the game fail flag is raised
	{
		// Display fail message


		Buzzer_buzz(0);
		Leds_allOff();
		gameControl.gameFailFlag = FALSE; // Disable the flag
	    gameControl.currentGame = FAIL; // Reset the game
	    SD_Overwrite(GAMECONTROL_FILENAME, "0", 1); // Save to the sd card
	}

	if (gameControl.gameSuccessFlag) // If the game success flag is raised
	{
		Buzzer_buzz(0);
		Leds_allOff();

	    gameControl.gameSuccessFlag = FALSE; // Disable the flag

	    if (gameControl.currentGame == VICTORY || gameControl.currentGame == FAIL)
	    {
	    	SD_Rmfile("0:/log.txt");
	    	SD_Overwrite(GAMECONTROL_FILENAME, "0", 1); // Save to the sd card
	    	gameControl.currentGame = TUTORIAL; // Reset the game
	    }
	    else
	    {

	    	gameControl.currentGame++;

	    	switch (gameControl.currentGame) { // Save current game level to storage
	    	case LOCATION:
	    	    SD_Overwrite(GAMECONTROL_FILENAME, "1", 1);
	    	    break;
	    	case MEMORY:
	    	    SD_Overwrite(GAMECONTROL_FILENAME, "2", 1);
	    	    break;
	    	case QUIZ:
	    	    SD_Overwrite(GAMECONTROL_FILENAME, "3", 1);
	    	    break;
	    	case PROXIMITY:
	    	    SD_Overwrite(GAMECONTROL_FILENAME, "4", 1);
	    	    break;
	    	case PIN:
	    	    SD_Overwrite(GAMECONTROL_FILENAME, "5", 1);
	    	    break;
	    	case VICTORY:
	    	    SD_Overwrite(GAMECONTROL_FILENAME, "6", 1);
	    	    break;
	    	default:
	    		break;
	    	}
	    }
	}
}
