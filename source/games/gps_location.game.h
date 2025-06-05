/*
 * gps_location.game.h
 *
 *  Created on: Apr 10, 2025
 *      Author: yalukaiwo
 */

#ifndef GAMES_GPS_LOCATION_GAME_H_
#define GAMES_GPS_LOCATION_GAME_H_

#include "../utils/GPS.h"
#include "../utils/SD.h"
#include "stdlib.h"
#include "stdio.h"
#include "game_control.h"
#include "math.h"

#define LOCATION_RADIUS_M 10
#define LOCATIONGAME_FILENAME "gpsLD.txt"

typedef struct {
	location_t location;
} GPS_location_game_props_t;

void initGPSLocationGame();
void gpsLocationGame();

#endif /* GAMES_GPS_LOCATION_GAME_H_ */
