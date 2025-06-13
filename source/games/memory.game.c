/*
 * memory.game.c
 *
 *  Created on: Jun 12, 2025
 *      Author: yalukaiwo
 */


#include "memory.game.h"

int sequences[5][5];
int currentRound = 0;
round_state_t roundState = M_TUTORIAL;
int currentDisplaying = 0;
int currentReading = 0;

int isDisplaying = 0;
long prevDisplayMillis = 0;
long displayingMillis = 0;


void initMemoryGame()
{
	// Fill the memory game

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < i + 1; j++) {
		    srand(time(NULL));
			int r = rand() % 4;

			sequences[i][j] = r;
		}
	}
}

void memoryGame()
{
	long currentMillis = millis();
	game_controller_t *gameControl = getGameControl();

	if (currentRound == 5) {
		gameControl->gameSuccessFlag = TRUE;
	}

	if (roundState == M_TUTORIAL) {
		roundState = DISPLAYING;
	}

	if (roundState == DISPLAYING) {
		if (!isDisplaying && currentMillis - prevDisplayMillis > 500) {
			if (currentDisplaying > currentRound) { // If everything from the round was displayed
				roundState = READING;
				currentReading = 0;
			}


			// Leds_allOff();
			// Leds_on(sequences[currentRound][currentDisplaying])
			// Buzzer_buzz(something)

			displayingMillis = currentMillis(); // Log start time
			isDisplaying = 1;
		}

		if (isDisplaying && currentMillis - displayingMillis > 500) { // If the led has been displaying for more than 500ms
			// Leds_allOff();
			// Buzzer_buzz(0);

			isDisplaying = 0;
			prevDisplayMillis = currentMillis; // Log stop time
			currentDisplaying++;

		}
	}

	if (roundState == READING) {
		if (currentReading > currentRound) {
			currentRound++;
			roundState = DISPLAYING;
			currentDisplaying = 0;
		}
	}

}
