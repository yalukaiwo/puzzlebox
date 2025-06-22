#include "Keypad.h"

// Define your own digital I/O modes and values
#define INPUT_PULLUP 0
#define OUTPUT 1
#define LOW 0
#define HIGH 1

extern void digital_write(uint8_t pin, uint8_t value);
extern uint8_t digital_read(uint8_t pin);

// Keypad configuration
#define ROWS 4
#define COLS 4

uint8_t colPins[COLS] = {7, 31, 11, 10};  // your row pins
uint8_t rowPins[ROWS] = {9, 8, 7, 6};  // your column pins

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

void Keypad_init(void) {
    // Initialize column pins as outputs set HIGH (inactive)
    MRCC0->MRCC_GLB_CC1 |= MRCC_MRCC_GLB_CC1_GPIO3(1);
    MRCC0->MRCC_GLB_CC1 |= MRCC_MRCC_GLB_CC1_PORT3(1);
    MRCC0->MRCC_GLB_CC1 |= MRCC_MRCC_GLB_CC1_GPIO2(1);
    MRCC0->MRCC_GLB_CC0 |= MRCC_MRCC_GLB_CC0_PORT2(1);

    // PORT3: [1] = Peripheral is released from reset
    // GPIO3: [1] = Peripheral is released from reset
    MRCC0->MRCC_GLB_RST1 |= MRCC_MRCC_GLB_RST1_GPIO3(1);
    MRCC0->MRCC_GLB_RST1 |= MRCC_MRCC_GLB_RST1_PORT3(1);
    MRCC0->MRCC_GLB_RST1 |= MRCC_MRCC_GLB_RST1_GPIO2(1);
    MRCC0->MRCC_GLB_RST0 |= MRCC_MRCC_GLB_RST0_PORT2(1);

    PORT2->PCR[7] = PORT_PCR_MUX(0) | PORT_PCR_LK(1) | PORT_PCR_IBE(1);
    PORT3->PCR[31] = PORT_PCR_MUX(0) | PORT_PCR_LK(1) | PORT_PCR_IBE(1);
    PORT3->PCR[11] = PORT_PCR_MUX(0) | PORT_PCR_LK(1) | PORT_PCR_IBE(1);
    PORT3->PCR[10] = PORT_PCR_MUX(0) | PORT_PCR_LK(1) | PORT_PCR_IBE(1);

	GPIO2->PSOR = (1 << 7);
    GPIO3->PSOR = (1 << 31);
    GPIO3->PSOR = (1 << 11);
    GPIO3->PSOR = (1 << 10);

    GPIO3->PDDR |= (1 << 31) | (1 << 11) | (1 << 10);
    GPIO2->PDDR |= (1 << 7);

    // Set pin function to GPIO and enable internal pull-up (if needed)
    PORT3->PCR[9] = PORT_PCR_MUX(0) | PORT_PCR_PE(1) | PORT_PCR_PS(1) | PORT_PCR_LK(1) | PORT_PCR_IBE(1);
    PORT3->PCR[8] = PORT_PCR_MUX(0) | PORT_PCR_PE(1) | PORT_PCR_PS(1) | PORT_PCR_LK(1) | PORT_PCR_IBE(1);
    PORT3->PCR[7] = PORT_PCR_MUX(0) | PORT_PCR_PE(1) | PORT_PCR_PS(1) | PORT_PCR_LK(1) | PORT_PCR_IBE(1);
    PORT3->PCR[6] = PORT_PCR_MUX(0) | PORT_PCR_PE(1) | PORT_PCR_PS(1) | PORT_PCR_LK(1) | PORT_PCR_IBE(1);

    // Set direction to input (clear bit = input)
    GPIO3->PDDR &= ~(1 << 9);  //
    GPIO3->PDDR &= ~(1 << 8);  //
    GPIO3->PDDR &= ~(1 << 7);  //
    GPIO3->PDDR &= ~(1 << 6);  //
}

void digitalWrite(int pin, int value, int isCols) {
	if (isCols == 1) {
	if (value == LOW) {
		if (pin == 7) {
			GPIO2->PCOR = (1 << pin);
			return;
		}

		GPIO3->PCOR = (1 << pin);
		return;
	}

	if (value == HIGH) {
		if (pin == 7) {
			GPIO2->PSOR = (1 << pin);
			return;
		}

		GPIO3->PSOR = (1 << pin);
		return;
	}
	} else {
		if (value == LOW) {
			GPIO3->PCOR = (1 << pin);
			return;
		}

		if (value == HIGH) {
			GPIO3->PSOR = (1 << pin);
			return;
		}

	}
}

int digitalRead(int pin, int isCols) {
	if (!isCols) {
    switch (pin) {
    	case 9: return !(GPIO3->PDIR & (1 << 9));  // Active low
        case 8: return !(GPIO3->PDIR & (1 << 8));
        case 7: return !(GPIO3->PDIR & (1 << 7));
        case 6: return !(GPIO3->PDIR & (1 << 6));
    }
	} else {
		switch(pin) {
		case 31: return !(GPIO3->PDIR & (1 << 31));  // Active low
		case 11: return !(GPIO3->PDIR & (1 << 11));
		case 7: return !(GPIO2->PDIR & (1 << 7));
		case 10: return !(GPIO3->PDIR & (1 << 10));
		}
	}
}

void pinMode(int pin, int isRead, int isCols) {
	volatile GPIO_Type *gpio;

	    // Determine GPIO port
	    if (pin == 7 && isCols) {
	        gpio = GPIO2;  // col pin 7 is on GPIO2
	    } else {
	        gpio = GPIO3;  // all other pins are on GPIO3
	    }

	    if (isRead) {
	        // Set as input (clear bit)
	        gpio->PDDR &= ~(1 << pin);
	    } else {
	        // Set as output (set bit)
	        gpio->PDDR |= (1 << pin);
	    }
}


char Keypad_getKey(void) {

	for (int i = 0; i < ROWS; i++) pinMode(rowPins[i], 1, 0);

	for (int i = 0; i < COLS; i++)
	{
		pinMode(colPins[i], 0, 1);
		digitalWrite(colPins[i], LOW, 1);

		for (int j = 0; j < ROWS; j++)
		{
			if (digitalRead(rowPins[j], 0)) {
				digitalWrite(colPins[i], HIGH, 1);
				pinMode(colPins[i], 1, 1);
				return keys[j][i];
			}
		}

		digitalWrite(colPins[i], HIGH, 1);
		pinMode(colPins[i], 1, 1);
	}

    return 'N';  // no key pressed
}
