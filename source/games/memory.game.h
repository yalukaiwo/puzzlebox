/*
 * memory.game.h
 *
 *  Created on: Jun 12, 2025
 *      Author: yalukaiwo
 */

#ifndef GAMES_MEMORY_GAME_H_
#define GAMES_MEMORY_GAME_H_

#include <stdlib.h>
#include <time.h>
#include "../utils/Millis.h"
#include "game_control.h"
#include "../utils/Buzzer.h"
#include "../utils/Buttons.h"
#include "../utils/Leds.h"
#include <stdio.h>

typedef enum RoundState {
	DISPLAYING,
	READING,
	M_TUTORIAL
} round_state_t;

void initMemoryGame();

void memoryGame();

#endif /* GAMES_MEMORY_GAME_H_ */
