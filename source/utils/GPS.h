/*
 * GPS.h
 *
 *  Created on: Mar 23, 2025
 *      Author: yalukaiwo
 */

#ifndef UTILS_GPS_H_
#define UTILS_GPS_H_

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
	double HDOP;
	unsigned short satelliteNumber;
} connection_t;

typedef struct GPS {
	void (*updateData)(); // Update gps data
	void (*setDestination)(double latitude, char latDirection, double longitude, char longDirection); // Set the destination coordinates
	directions_t* (*getCurrentDirections)(); // Get current directions to the destination
	location_t* (*getCurrentLocation)(); // Get the current location of the object
	connection_t* (*getConnectionQuality)(); // Get connection quality parameters
	int (*isLocationRelevant)(); // Get whether last gps ping was recently (1 / 0)
} GPS_t;

// Available functions outside module

GPS_t initGPS();

#endif /* UTILS_GPS_H_ */
