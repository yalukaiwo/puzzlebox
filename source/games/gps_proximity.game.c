/*
 * gps_proximity.game.c
 *
 *  Created on: Apr 11, 2025
 *      Author: yalukaiwo
 */

#include "gps_proximity.game.h"
#include "../utils/GPS.h"
#include "stdio.h"
#include "game_control.h"
#include "math.h"

GPS_proximity_game_props_t proximityGameProps;

void initGPSProximityGame() {
	// get the gps location from SD
	// SD.get("gps_location_game_place")

    // set the destination
	proximityGameProps.location.latitude = 51.989105;
	proximityGameProps.location.latDirection = 'N';

	proximityGameProps.location.longitude = 5.948583;
	proximityGameProps.location.longDirection = 'E';

}

void gpsProximityGame() {
	GPS_t *GPS = getGPS(); // Get the GPS instance
	game_controller_t *gameControl = getGameControl();
	// LCD_t *LCD = getLCD();

	GPS->setDestination(proximityGameProps.location.latitude, proximityGameProps.location.latDirection, proximityGameProps.location.longitude, proximityGameProps.location.longDirection); // Should be gotten from game props

	directions_t *directions = GPS->getCurrentDirections();

	double distance = sqrt((pow(directions->lat_d, 2) + pow(directions->long_d,2))); // Calculate the distance to the target using pythagoras
	double proximityInPercent;

	if (distance > 200)
	{
		proximityInPercent = 0;
	}
	else
	{
		proximityInPercent = 1 - (distance / 200);
	}

	printf("HDOP: %.2lf\r\n", GPS->getConnectionQuality()->HDOP);
	printf("distance: %.2lf",  distance);
	printf("proximity: %.2lf", proximityInPercent);

	if (distance < LOCATION_RADIUS_M) {
		// success
		printf("Success");
		gameControl->gameSuccessFlag = true;
	}

	// buzz the buzzer and display on lcd (maybe)
	// Buzzer.buzz(255 * proximityInPercent);
}
