/*
 * pin.game.h
 *
 *  Created on: 5 Jun 2025
 *      Author: safin
 */

#ifndef GAMES_PIN_GAME_H_
#define GAMES_PIN_GAME_H_

#include "../utils/LCD.h"
#include "../utils/Keypad.h"
#include "../utils/SD.h"
#include "../utils/Millis.h"

#include "game_control.h"

#include "stdlib.h"
#include "string.h"

#define PINGAME_FILENAME "pin.txt"

void initPinGame();

char* getPin();
void pinGame();

#endif /* GAMES_PIN_GAME_H_ */
