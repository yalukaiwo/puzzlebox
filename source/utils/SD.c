/*
 * SD.c
 *
 *  Created on: May 23, 2025
 *      Author: yalukaiwo
 */

#include "SD.h"


FATFS fatFs;
FIL file;
UINT bw, br;
FRESULT fr;

void SD_Rmfile(char *filename) {
	f_unlink(filename);
}

void SD_Init()
{
	fr = f_mount(&fatFs, "", 1);		// Give a work area to the default drive
	if (fr != FR_OK) {
		printf("Mount failed %d\r\n", fr);
		LCD_print("SD EMPTY / CORR", "");
		while (1);
	}

	printf("Mount successful");
}

void SD_Writeln(char* filename, char* data, int size)
{
	fr = f_open(&file, filename, FA_WRITE | FA_OPEN_APPEND);	// Create a file if it doesn't exist, else append
	if (fr == FR_OK) {
		f_printf(&file, "%s\r\n", data);	// Write data to the file

		fr = f_close(&file);
	}
}

void SD_Overwrite(char *filename, char* data, int size) {
	fr = f_open(&file, filename, FA_WRITE | FA_CREATE_ALWAYS); // Always replace the file
	if (fr == FR_OK) {
		f_write(&file, data, size, &bw);
		fr = f_close(&file);
	}
}

int SD_Read(char *filename, char *buffer, int size) {
	fr = f_open(&file, filename, FA_READ);

	if (fr == FR_NO_FILE) { // If file doesn't exist, return 0
		return 0;
	}

	if (fr == FR_OK) {
		f_read(&file, buffer, size-1, &br);
		buffer[br] = '\0';
		f_close(&file);
		return 1;
	}
}
