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
	PIN
} game_t;
typedef enum Flag
{
	false = 0,
	true = 1
} flag_t;

typedef struct Game_Control
{
	game_t currentGame;
	flag_t gameSuccessFlag;
	flag_t gameFailFlag;
} game_controller_t;


game_controller_t * initGameControl();
game_controller_t * getGameControl();
void checkGameStatus();


#endif /* GAME_CONTROL_H_ */
