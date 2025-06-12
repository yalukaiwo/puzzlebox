#ifndef TRIVIA_H
#define TRIVIA_H

#include <stdint.h>
#include <stdbool.h>

#define TOTAL_QUESTIONS 10
#define QUIZ_SIZE 5
#define MAX_LIVES 3

typedef struct {
    const char *question;
    const char *options[4];
    char correct;
} TriviaQuestion;

bool Trivia_RunGame(void);

#endif // TRIVIA_H
