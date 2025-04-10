/*
 * GPS.c
 *
 *  Created on: Mar 23, 2025
 *      Author: yalukaiwo
 */

#include "GPS.h"
#include "math.h"
#include "../lpuart2_interrupt.h"

// LOCAL VARIABLES

GPS_t GPS; // The module itself

location_t currentLocation; // Current user location
location_t targetLocation; // Target user location
directions_t directions; // Direction from current location to target location
connection_t connectionQuality; // Quality of the connection data
int noFixLoops = 100; // Amount of loops without a fix

char buffer[100];

// Function Prototypes

void updateData(); // Update the current data of the GPS
void setDestination(double latitude, char latDirection, double longitude, char longDirection); // Update target destination
location_t* getCurrentLocation(); // Get the current location
connection_t* getConnectionQuality(); // Get the connection quality
directions_t* getCurrentDirections(); // Get the current directions
int isLocationRelevant(); // Check relevance of the location
void parseGNGGA(char *buffer, location_t *location, connection_t *connection); // Parse the GNGGA string
void GPSCalculateDirections(directions_t *directions, location_t *origin, location_t *destination); // Calculate directions to the destination
double calculateLongitudeDistance(double fromLong, double toLong, double latitude); // Calculate the distance to the destination long-wise
double calculateLatitudeDistance(double fromLat, double toLat); // Calculate the distance to the destination lat-wise
char determineLongitudeDirection(double fromLong, double toLong); // Get the long direction
char determineLatitudeDirection(double fromLat, double toLat); // Get the lat direction


// Initialization function

GPS_t initGPS() {
 GPS.getConnectionQuality = getConnectionQuality;
 GPS.getCurrentDirections = getCurrentDirections;
 GPS.getCurrentLocation = getCurrentLocation;
 GPS.isLocationRelevant = isLocationRelevant;
 GPS.setDestination = setDestination;
 GPS.updateData = updateData;

 return GPS;
}

// Public functions

void updateData() {
	while (lpuart2_rxcnt() > 0)
	{
		char c = lpuart2_getchar(); // Receive char from buffer

	    strncat(buffer, &c, 1); // Add character to the buffer

	    if (c == '\n') // If the character is a newline character
    	{
	    	if (strncmp(buffer, "$GNGGA", 6) == 0) // Determine whether the line is desired
	        {
	    		parseGNGGA(buffer, &currentLocation, &connectionQuality); // Parse the line
	        	GPSCalculateDirections(&directions, &currentLocation, &targetLocation); // Calculate directions based on new data
	        	buffer[0] = '\0'; // Reset the buffer
	        }
	    	else
	        {
	    		buffer[0] = '\0'; // Reset the buffer
	        }
    	}
	}
}

void setDestination(double latitude, char latDirection, double longitude, char longDirection) {
	// Set the parameters accordingly and recalculate directions
	targetLocation.latitude = latitude;
	targetLocation.latDirection = latDirection;
	targetLocation.longitude = longitude;
	targetLocation.longDirection = longDirection;

	GPSCalculateDirections(&directions, &currentLocation, &targetLocation);
}

location_t* getCurrentLocation() {
	return &currentLocation;
}

directions_t* getCurrentDirections() {
	return &directions;
}

connection_t* getConnectionQuality() {
	return &connectionQuality;
}

int isLocationRelevant() {
	return noFixLoops < 10; // If the program went 10 loops without a fix, connection deemed unreliable
}

// Internal functions

void parseGNGGA(char *buffer, location_t *location, connection_t *connection)
{
	char *token = strtok(buffer, ","); // Tokenize the string
	int index = 0;

	while (token != NULL) {
		index++;

		double rawValue;
		int degrees;
		double minutes;

		switch (index)
		{
		case 3: // Latitude
			rawValue = atof(token);
			degrees = (int)(rawValue / 100); // Extract degrees
			minutes = rawValue - (degrees * 100); // Extract minutes
			location->latitude = degrees + (minutes / 60);
			break;
		case 4: // Lat direction
			location->latDirection = *token;
			break;
		case 5: // Longitude
			rawValue = atof(token);
			degrees = (int)(rawValue / 100);  // Extract degrees
			minutes = rawValue - (degrees * 100);  // Extract minutes
			location->longitude = degrees + (minutes / 60);
			break;
		case 6: // Long direction
			location->longDirection = *token;
			break;
		case 7: // Fix type
			if (atoi(token) == 0) // 0 - no fix
			{
				noFixLoops++;
			}
			else
			{
				noFixLoops = 0;
			}
		case 8: // Satellite count
			connection->satelliteNumber = atoi(token);
		    break;
		case 9: // HDOP
			connection->HDOP = atof(token);
		    break;
		}

		if (location->latDirection == 'S') location->latitude = -(location->latitude);
		if (location->longDirection == 'W') location->longitude = -(location->longitude);

		token = strtok(NULL, ",");
	}
}

void GPSCalculateDirections(directions_t *directions, location_t *origin, location_t *destination)
{
	// Calculate distances and set them accordingly
	directions->long_d = calculateLongitudeDistance(origin->longitude, destination->longitude, origin->latitude);
	directions->lat_d = calculateLatitudeDistance(origin->latitude, destination->latitude);
	directions->longDirection = determineLongitudeDirection(origin->longitude, destination->longitude);
	directions->latDirection = determineLatitudeDirection(origin->latitude, destination->latitude);
}

double calculateLongitudeDistance(double fromLong, double toLong, double latitude) {
  double delta_lon = fabs(toLong - fromLong);  // Calculate the absolute difference between longitudes

  double distance = DEGREE_TO_RAD(delta_lon) * EARTH_RADIUS_M * cos(DEGREE_TO_RAD(latitude)); // Distance formula

  return distance;
}

double calculateLatitudeDistance(double fromLat, double toLat) {
    double delta_lat = fabs(toLat - fromLat); // Calculate the absolute difference between latitudes

    double distance = DEGREE_TO_RAD(delta_lat) * EARTH_RADIUS_M; // Convert latitude difference to radians

    return distance;
}

char determineLongitudeDirection(double fromLong, double toLong) {
    if (toLong > fromLong) {
        return 'E';
    } else {
        return 'W';  // Same longitude
    }
}

char determineLatitudeDirection(double fromLat, double toLat) {
    if (toLat > fromLat) {
        return 'N';
    } else {
        return 'S';  // Same latitude
    }
}
