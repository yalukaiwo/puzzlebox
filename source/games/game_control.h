/*
 * game_control.h
 *
 *  Created on: Apr 10, 2025
 *      Author: yalukaiwo
 */

#ifndef GAME_CONTROL_H_
#define GAME_CONTROL_H_

#include "../utils/Buzzer.h"
#include "../utils/Leds.h"

typedef enum Games
{
	TUTORIAL,
	LOCATION,
	MEMORY,
	SHOW_PIN,
	QUIZ,
	PROXIMITY,
	PIN,
	VICTORY,
	FAIL
} game_t;

typedef enum Flag
{
	FALSE = 0,
	TRUE = 1
} flag_t;

typedef struct Game_Control
{
	game_t currentGame;
	flag_t gameSuccessFlag;
	flag_t gameFailFlag;
} game_controller_t;

#define GAMECONTROL_FILENAME "gameS.txt"


game_controller_t * initGameControl();
game_controller_t * getGameControl();
void checkGameStatus();


#endif /* GAME_CONTROL_H_ */
