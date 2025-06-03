/*
 * game_control.h
 *
 *  Created on: Apr 10, 2025
 *      Author: yalukaiwo
 */

#ifndef GAME_CONTROL_H_
#define GAME_CONTROL_H_

#include <stdbool.h>  // Use standard boolean type

typedef enum Games
{
	TUTORIAL,
	LOCATION,
	MEMORY,
	QUIZ,
	PROXIMITY,
	PIN
} game_t;

typedef struct Game_Control
{
	game_t currentGame;
	bool gameSuccessFlag;
	bool gameFailFlag;
} game_controller_t;

game_controller_t * initGameControl();
game_controller_t * getGameControl();
void checkGameStatus();

#endif /* GAME_CONTROL_H_ */
