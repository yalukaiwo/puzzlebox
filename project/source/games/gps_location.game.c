/*
 * gps_location.game.c
 *
 *  Created on: Apr 10, 2025
 *      Author: yalukaiwo
 */

#include "gps_location.game.h"
#include "../utils/GPS.h"
#include "stdio.h"
#include "game_control.h"
#include "math.h"

GPS_location_game_props_t locationGameProps;

void initGPSLocationGame() {
	// get the gps location from SD
	// SD.get("gps_location_game_place")

    // set the destination
	locationGameProps.location.latitude = 51.989409;
	locationGameProps.location.latDirection = 'N';

	locationGameProps.location.longitude = 5.948003;
	locationGameProps.location.longDirection = 'E';

}

void gpsLocationGame() {
	GPS_t *GPS = getGPS(); // Get the GPS instance
	game_controller_t *gameControl = getGameControl();
	// LCD_t *LCD = getLCD();

	GPS->setDestination(locationGameProps.location.latitude, locationGameProps.location.latDirection, locationGameProps.location.longitude, locationGameProps.location.longDirection); // Should be gotten from game props

	directions_t *directions = GPS->getCurrentDirections();

	double distance = sqrt((pow(directions->lat_d, 2) + pow(directions->long_d,2))); // Calculate the distance to the target using pythagoras

	printf("HDOP: %.2lf\r\n", GPS->getConnectionQuality()->HDOP);
	printf("distance: %.2lf",  distance);

	if (distance < LOCATION_RADIUS_M) {
		// success
		printf("Success");
		gameControl->gameSuccessFlag = true;
	}

	// display the directions on the lcd display
	// LCD.print(2, "blabla");
	// LCD.print(3, "blabla");
}
