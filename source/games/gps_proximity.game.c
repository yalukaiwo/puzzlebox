/*
 * gps_proximity.game.c
 *
 *  Created on: Apr 11, 2025
 *      Author: yalukaiwo
 */

#include "gps_proximity.game.h"


GPS_proximity_game_props_t proximityGameProps;
int buzzDelay = 1000;
long prevBuzzMillis = 0;
long prevBuzzStartMillis = 0;
int isBuzzing = 0;

void initGPSProximityGame() {
		char buffer[23] = {'\0'};
		char *bufPtr = buffer;

		int res = SD_Read(PROXIMITYGAME_FILENAME, buffer, sizeof(buffer) / sizeof(char));


		if (res == 0) { // If file does not exist
			printf("No location game data file found");
			while (1) {}
		}

		// set the data to blank
		proximityGameProps.location.latitude = 0;
		proximityGameProps.location.latDirection = 'X';

		proximityGameProps.location.longitude = 0;
		proximityGameProps.location.longDirection = 'X';

		char *token = strsep(&bufPtr, ","); // Tokenize the buffer
		int index = 0; // Token index

		while (token != NULL) { // Parse through tokens
			index++;

			switch(index) {
			case 1:
				proximityGameProps.location.latitude = atof(token);
				break;
			case 2:
				proximityGameProps.location.latDirection = token[0];
				break;
			case 3:
				proximityGameProps.location.longitude = atof(token);
				break;
			case 4:
				proximityGameProps.location.longDirection = token[0];
				break;
			}


			token = strsep(&bufPtr, ",");
		}

		if (proximityGameProps.location.latitude == 0 || proximityGameProps.location.latDirection == 'X' || proximityGameProps.location.longitude == 0 || proximityGameProps.location.longDirection == 'X') {
			printf("Invalid location game data");
			while (1) {}
		}

}

void gpsProximityGame() {
	game_controller_t *gameControl = getGameControl();
	long currentMillis = millis();


	GPS_setDestination(proximityGameProps.location.latitude, proximityGameProps.location.latDirection, proximityGameProps.location.longitude, proximityGameProps.location.longDirection); // Should be gotten from game props

	directions_t *directions = GPS_getCurrentDirections();

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

	printf("HDOP: %.2lf\r\n", GPS_getConnectionQuality()->HDOP);
	printf("distance: %.2lf",  distance);
	printf("proximity: %.2lf", proximityInPercent);

	if (distance < LOCATION_RADIUS_M) {
		// success
		printf("Success");
		gameControl->gameSuccessFlag = TRUE;
	}

	LCD_print("Proximity game  ", "                ");

	buzzDelay = 1000 * (1-proximityInPercent);

	if (!!isBuzzing && currentMillis - prevBuzzStartMillis >= 200) {
		isBuzzing = 0;
		prevBuzzMillis = currentMillis;
		Buzzer_buzz(0);
	};

	if (!isBuzzing && currentMillis - prevBuzzMillis >= buzzDelay) {
		isBuzzing = 1;
		prevBuzzStartMillis = currentMillis;
		Buzzer_buzz(600);
	}
}
