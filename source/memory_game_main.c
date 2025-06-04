/*!
 * \file      memory_game_main.c
 * \brief     Entry point for the memory game application
 * \author    Adib
 */

#include "memory_game.h"

int main(void) {
    // Initialize the memory game system (buttons, LEDs, buzzer)
    memory_game_init();

    // Start the game loop
    memory_game_loop();

    // Infinite loop (program should not reach here normally)
    while (1) {
    }
}
