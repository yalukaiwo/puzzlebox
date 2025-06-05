/*
 * gps_location.game.c
 *
 *  Created on: Apr 10, 2025
 *      Author: yalukaiwo
 */

#include "gps_location.game.h"

GPS_location_game_props_t locationGameProps;

void initGPSLocationGame() {

	char buffer[23] = {'\0'};
	char *bufPtr = buffer;

	int res = SD_Read(LOCATIONGAME_FILENAME, buffer, sizeof(buffer)/sizeof(char));


	if (res == 0) { // If file does not exist
		printf("No location game data file found");
		while (1) {}
	}

	// set the data to blank
	locationGameProps.location.latitude = 0;
	locationGameProps.location.latDirection = 'X';

	locationGameProps.location.longitude = 0;
	locationGameProps.location.longDirection = 'X';

	char *token = strsep(&bufPtr, ","); // Tokenize the buffer
	int index = 0; // Token index

	while (token != NULL) { // Parse through tokens
		index++;

		switch(index) {
		case 1:
			locationGameProps.location.latitude = atof(token);
			break;
		case 2:
			locationGameProps.location.latDirection = token[0];
			break;
		case 3:
			locationGameProps.location.longitude = atof(token);
			break;
		case 4:
			locationGameProps.location.longDirection = token[0];
			break;
		}


		token = strsep(&bufPtr, ",");
	}

	if (locationGameProps.location.latitude == 0 || locationGameProps.location.latDirection == 'X' || locationGameProps.location.longitude == 0 || locationGameProps.location.longDirection == 'X') {
		printf("Invalid location game data");
		while (1) {}
	}
}

void gpsLocationGame() {
	game_controller_t *gameControl = getGameControl();
	// LCD_t *LCD = getLCD();

	GPS_setDestination(locationGameProps.location.latitude, locationGameProps.location.latDirection, locationGameProps.location.longitude, locationGameProps.location.longDirection); // Should be gotten from game props

	directions_t *directions = GPS_getCurrentDirections();

	double distance = sqrt((pow(directions->lat_d, 2) + pow(directions->long_d,2))); // Calculate the distance to the target using pythagoras

	printf("HDOP: %.2lf\r\n", GPS_getConnectionQuality()->HDOP);
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
