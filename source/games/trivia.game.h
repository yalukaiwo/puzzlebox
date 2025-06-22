#ifndef TRIVIA_GAME_H
#define TRIVIA_GAME_H

#ifdef __cplusplus
extern "C" {
#endif

// Initializes the trivia game state (shuffle, reset lives, etc.)
void initTriviaGame(void);

// Main trivia game loop logic (to be called repeatedly)
void triviaGame(void);

#ifdef __cplusplus
}
#endif

#endif // TRIVIA_GAME_H
