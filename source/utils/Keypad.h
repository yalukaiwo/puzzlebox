/*
 * Keypad.h
 *
 *  Created on: 5 Jun 2025
 *      Author: safin
 */

#ifndef UTILS_KEYPAD_H_
#define UTILS_KEYPAD_H_

#include <MCXA153.h>
#include "stdint.h"

void Keypad_init(void);
char Keypad_getKey(void);

#endif /* UTILS_KEYPAD_H_ */
