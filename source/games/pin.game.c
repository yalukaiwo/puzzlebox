#include "pin.game.h"

char code[5];
char guess[5] = "****";
int currentDigit = 0;
int attempt = 0;
long lastReadMillis = 0;

void initPinGame() {
	game_controller_t *gameControl = getGameControl();

	char buffer[5] = {'\0'};
	char *bufPtr = buffer;

	srand(millis());
	int secret_code = (rand() % 9000) + 1000;

	int res = SD_Read(PINGAME_FILENAME, buffer, sizeof(buffer)/sizeof(char));

	if (!res || gameControl->currentGame == TUTORIAL || gameControl->currentGame == FAIL) {
		sprintf(code, "%4d", secret_code);
		SD_Overwrite(PINGAME_FILENAME, code, sizeof(code)/sizeof(char));
	} else {
		strcpy(code, buffer);
	}
}

char *getPin() {
	return code;
}

void pinGame() {
	long currentMillis = millis();
	game_controller_t *gameControl = getGameControl();

	char buffer[17];
	sprintf(buffer, "      %4s      ", guess);
	LCD_print("Enter the PIN:  ", buffer);

	if (currentDigit == 4) {
		if (!strcmp(code, guess)) {
			gameControl->gameSuccessFlag = TRUE;
			currentDigit = 0;
		}
		else {
			attempt++;
			strcpy(guess, "****");
			currentDigit = 0;
		}
	}


	if (currentMillis - lastReadMillis > 500) {
		switch (Keypad_getKey()) {
		case '1':
			guess[currentDigit] = '1';
			currentDigit++;
			lastReadMillis = currentMillis;
			break;
		case '2':
			guess[currentDigit] = '2';
			currentDigit++;
			lastReadMillis = currentMillis;
			break;
		case '3':
			guess[currentDigit] = '3';
			currentDigit++;
			lastReadMillis = currentMillis;
			break;
		case '4':
			guess[currentDigit] = '4';
			currentDigit++;
			lastReadMillis = currentMillis;
			break;
		case '5':
			guess[currentDigit] = '5';
			currentDigit++;
			lastReadMillis = currentMillis;
			break;
		case '6':
			guess[currentDigit] = '6';
			currentDigit++;
			lastReadMillis = currentMillis;
			break;
		case '7':
			guess[currentDigit] = '7';
			currentDigit++;
			lastReadMillis = currentMillis;
			break;
		case '8':
			guess[currentDigit] = '8';
			currentDigit++;
			lastReadMillis = currentMillis;
			break;
		case '9':
			guess[currentDigit] = '9';
			currentDigit++;
			lastReadMillis = currentMillis;
			break;
		case '#':
			if (!strcmp(code, guess)) {
				gameControl->gameSuccessFlag = TRUE;
				currentDigit = 0;
			}
			else {
				attempt++;
				strcpy(guess, "****");
				currentDigit = 0;
			}
			break;
		default:
			break;
		}
	}

	if (attempt == 3) {
		gameControl->gameFailFlag = TRUE;
		currentDigit = 0;
		attempt = 0;
	}
}
