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

long prevReadMillis = 0;

int isSwitchingRounds = 0;
long switchingRoundsMillis = 0;
int switchingRoundsCount = 0;


void initMemoryGame()
{
	// Fill the memory game

	srand(millis());
	int r = rand() % 3;

	sequences[0][0] = r;

	sequences[5][5];
	currentRound = 0;
	roundState = M_TUTORIAL;
	currentDisplaying = 0;
	currentReading = 0;

	isDisplaying = 0;
	prevDisplayMillis = 0;
	displayingMillis = 0;

	prevReadMillis = 0;

	isSwitchingRounds = 0;
	switchingRoundsMillis = 0;
	switchingRoundsCount = 0;

}

void memoryGame()
{
	LCD_print("Memory game     ", "                ");
	long currentMillis = millis();
	game_controller_t *gameControl = getGameControl();


	if (currentRound == 5) {
		gameControl->gameSuccessFlag = TRUE;
		return;
	}

	if (currentMillis - switchingRoundsMillis < 500 && isSwitchingRounds) {
		switch (switchingRoundsCount) {
		case 0:
			Leds_allOff();
			Buzzer_buzz(0);
			return;
		case 1:
			Leds_allOn();
			Buzzer_buzz(500);
			return;
		case 2:
			Leds_allOff();
			Buzzer_buzz(0);
			return;
		}
	} else if (isSwitchingRounds) {
		if (switchingRoundsCount == 2) {
			isSwitchingRounds = 0;
			return;
		}

		switchingRoundsCount++;
		switchingRoundsMillis = currentMillis;
		return;
	}

	if (roundState == M_TUTORIAL) {

		LCD_print("Memory game     ", "Press to next   ");
		if (Buttons_isAnyPressed()) roundState = DISPLAYING;
		return;
	}

	if (roundState == DISPLAYING) {
		if (!isDisplaying && currentMillis - prevDisplayMillis > 500) {
			if (currentDisplaying > currentRound) { // If everything from the round was displayed
				currentReading = 0;
				roundState = READING;
				return;
			}


			Leds_allOff();
			Leds_on(sequences[currentRound][currentDisplaying]);
			Buzzer_buzz(1000);

			displayingMillis = currentMillis; // Log start time
			isDisplaying = 1;
			return;
		}

		if (isDisplaying && currentMillis - displayingMillis > 500) { // If the led has been displaying for more than 500ms
			Leds_allOff();
			Buzzer_buzz(0);

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
			isSwitchingRounds = 1;
			switchingRoundsCount = 0;
			switchingRoundsMillis = currentMillis;
			if (currentRound == 5) return;
			srand(millis());
			for (int i = 0; i < currentRound + 1; i++) {
				int r = rand() % 3;

				sequences[currentRound][i] = r;
			}
			return;
		}

		if (Buttons_isAnyPressed() &&  currentMillis - prevReadMillis >= 500) {
			if (Buttons_isPressed(sequences[currentRound][currentReading])) {
				currentReading++;
			} else {
				initMemoryGame();
				gameControl->gameFailFlag = 1;

			}

			prevReadMillis = currentMillis;
		}
	}
}
