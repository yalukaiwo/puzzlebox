/*
 * logger.c
 *
 *  Created on: Jun 1, 2025
 *      Author: yalukaiwo
 */

#include "Logger.h"

void Logger_updateData() {
	char logString[50];

	location_t *currentLocation = GPS_getCurrentLocation();
	connection_t *connection = GPS_getConnectionQuality();

	sprintf(logString, "%.2lf,%.6lf,%c,%.6lf,%c,%.2lf", connection->time,currentLocation->latitude,currentLocation->latDirection,currentLocation->longitude,currentLocation->longDirection,connection->HDOP);

	SD_Writeln(LOG_FILENAME, logString, sizeof(logString) / sizeof(char));
}
