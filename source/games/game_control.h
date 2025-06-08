/*
 * game_control.h
 *
 *  Created on: Apr 10, 2025
 *      Author: yalukaiwo
 */

#ifndef GAME_CONTROL_H_
#define GAME_CONTROL_H_

typedef enum Games
{
	TUTORIAL,
	LOCATION,
	MEMORY,
	QUIZ,
	PROXIMITY,
	PIN,
	VICTORY
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

#define GAME_STATUS_SUCCESS()   (getGameControl()->gameSuccessFlag = TRUE)
#define GAME_STATUS_FAILURE()   (getGameControl()->gameFailFlag = TRUE)


#endif /* GAME_CONTROL_H_ */
