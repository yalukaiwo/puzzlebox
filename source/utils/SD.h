/*
 * SD.h
 *
 *  Created on: May 23, 2025
 *      Author: yalukaiwo
 */

#ifndef UTILS_SD_H_
#define UTILS_SD_H_

#include <stdio.h>
#include <MCXA153.h>
#include "../fatFs/ff.h"



void SD_Init(); // Initialize sd
void SD_Writeln(char *filename, char *data, int size); // Append to the file
void SD_Overwrite(char *filename, char *data, int size); // Overwrite the file
int SD_Read(char *filename, char *buffer, int size); // Read from sd


#endif /* UTILS_SD_H_ */
