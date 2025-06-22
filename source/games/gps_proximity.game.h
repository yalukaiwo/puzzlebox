/*
 * gps_proximity.game.h
 *
 *  Created on: Apr 11, 2025
 *      Author: yalukaiwo
 */

#ifndef GAMES_GPS_PROXIMITY_GAME_H_
#define GAMES_GPS_PROXIMITY_GAME_H_

#include "../utils/GPS.h"
#include "../utils/SD.h"
#include "../utils/LCD.h"
#include "../utils/Buzzer.h"
#include "../utils/Millis.h"
#include "stdlib.h"
#include "stdio.h"
#include "game_control.h"
#include "math.h"

#define LOCATION_RADIUS_M 20
#define PROXIMITYGAME_FILENAME "gpsPD.txt"

typedef struct {
	location_t location;
} GPS_proximity_game_props_t;

void initGPSProximityGame();
void gpsProximityGame();

#endif /* GAMES_GPS_PROXIMITY_GAME_H_ */
