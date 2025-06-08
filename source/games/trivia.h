#ifndef TRIVIA_H
#define TRIVIA_H

#include <stdint.h>
#include <stdbool.h>

#define TOTAL_QUESTIONS 25
#define QUIZ_SIZE 6
#define MAX_LIVES 3

typedef struct {
    char question[41];     // max 40 characters + '\0'
    char options[4][16];   // 4 options, max 15 chars each + '\0'
    char correct;          // 'A', 'B', 'C', or 'D'
} TriviaQuestion;

/**
 * Runs the trivia game logic.
 * Returns true if user passes the game (at least half correct), false otherwise.
 */
bool Trivia_RunGame(void);

#endif // TRIVIA_H
