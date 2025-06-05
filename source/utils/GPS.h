/*
 * GPS.h
 *
 *  Created on: Mar 23, 2025
 *      Author: yalukaiwo
 */

#ifndef UTILS_GPS_H_
#define UTILS_GPS_H_

#include "math.h"
#include "stdlib.h"
#include "stdio.h"
#include <string.h>
#include "../lpuart2_interrupt.h"

// Defines

#define M_PI 3.141592
#define EARTH_RADIUS_M 6371000.0  // Earth's radius in meters
#define DEGREE_TO_RAD(x) ((x*M_PI) / 180.0)

// Structs

typedef struct Location {
  double longitude;
  double latitude;
  char latDirection;  // Latitude direction
  char longDirection; // Longitude direction
} location_t;

typedef struct Directions {
  double long_d; // Distance in meters longitude
  double lat_d;  // Distance in meters latitude
  char latDirection;  // Direction latitude
  char longDirection; // Direction longitude
} directions_t;

typedef struct Connection {
	double time;
	double HDOP;
	int satelliteNumber;
	int fixType;
} connection_t;

// Available functions outside module

void GPS_updateData(); // Update the current data of the GPS
void GPS_setDestination(double latitude, char latDirection, double longitude, char longDirection); // Update target destination
location_t* GPS_getCurrentLocation(); // Get the current location
connection_t* GPS_getConnectionQuality(); // Get the connection quality
directions_t* GPS_getCurrentDirections(); // Get the current directions
int GPS_isLocationRelevant(); // Check relevance of the location
char* strsep(char **stringp, const char *delim);


#endif /* UTILS_GPS_H_ */
