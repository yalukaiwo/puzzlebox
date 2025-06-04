/*
 * gps_location.game.h
 *
 *  Created on: Apr 10, 2025
 *      Author: yalukaiwo
 */

#ifndef GAMES_GPS_LOCATION_GAME_H_
#define GAMES_GPS_LOCATION_GAME_H_

#include "../utils/GPS.h"

#define LOCATION_RADIUS_M 10

typedef struct {
	location_t location;
} GPS_location_game_props_t;

void initGPSLocationGame();
void gpsLocationGame();

#endif /* GAMES_GPS_LOCATION_GAME_H_ */
