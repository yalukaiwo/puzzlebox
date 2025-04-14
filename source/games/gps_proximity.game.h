/*
 * gps_proximity.game.h
 *
 *  Created on: Apr 11, 2025
 *      Author: yalukaiwo
 */

#ifndef GAMES_GPS_PROXIMITY_GAME_H_
#define GAMES_GPS_PROXIMITY_GAME_H_

#include "../utils/GPS.h"

#define LOCATION_RADIUS_M 10

typedef struct {
	location_t location;
} GPS_proximity_game_props_t;

void initGPSProximityGame();
void gpsProximityGame();

#endif /* GAMES_GPS_PROXIMITY_GAME_H_ */
