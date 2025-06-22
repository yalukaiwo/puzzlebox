#include "../utils/LCD.h"
#include "../utils/Keypad.h"
#include "game_control.h"
#include "trivia.game.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVES 3
#define TOTAL_QUESTIONS 10
#define QUIZ_SIZE 5

typedef struct {
    const char *line1;
    const char *line2;
    char correct; // 'A', 'B', 'C', 'D'
} TriviaQ;

static TriviaQ question_pool[] = {
    {"2+2*2=?         ", "A:6 B:8 C:4 D:10", 'A'},
    {"15-4*3=?        ", "A:3 B:11 C:9 D:0", 'A'},
    {"(9+3)/3=?       ", "A:4 B:5 C:3     ", 'A'},
    {"7*2-6=?         ", "A:6 B:10 C:8    ", 'C'},
    {"Capital USA?    ", "A:DC B:NY C:TX  ", 'A'},
    {"Capital Japan?  ", "A:Os B:Tk C:Ky  ", 'B'},
    {"Boil temp (C)?  ", "A:90 B:80 C:100 ", 'C'},
    {"Fast land anim? ", "A:Ch B:Hr C:Tg  ", 'A'},
    {"Teeth count?    ", "A:28 B:30 C:32  ", 'C'},
    {"Has DNA?        ", "A:Virus B:H2O   ", 'A'}
};

// Game state variables
static int qIndex;
static int correctCount;
static int lives;
static bool showingFeedback;
static char lastAnswer;

void show(const char *l1, const char *l2, int delay_ms)
{
    LCD_print(l1, l2);
    int m = __get_PRIMASK();
    __disable_irq();
    if (delay_ms > 0) delay_us(delay_ms * 1000);
    __enable_irq();
    __set_PRIMASK(m);
}

static void shuffle_questions(void)
{
    for (int i = TOTAL_QUESTIONS - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        TriviaQ temp = question_pool[i];
        question_pool[i] = question_pool[j];
        question_pool[j] = temp;
    }
}

void initTriviaGame(void)
{
    qIndex = -2;
    correctCount = 0;
    lives = MAX_LIVES;
    showingFeedback = false;
    lastAnswer = 0;
}

void triviaGame(void)
{
	game_controller_t *gameControl = getGameControl();

    if (qIndex == -2) {
        shuffle_questions();
        show("TRIVIA TIME!    ", "Press A/B/C/D   ", 1500);
        show("5 Qs, 3 lives   ", "                ", 1000);
        qIndex = 0;
        return;
    }

    if (qIndex >= QUIZ_SIZE || lives == 0) {
        bool result = correctCount >= (QUIZ_SIZE / 2);
        if (result) {
            gameControl->gameSuccessFlag = TRUE;
        } else {
            gameControl->gameFailFlag = TRUE;
        }

        initTriviaGame(); // Reset for next time
        return;
    }

    if (!showingFeedback) {
        TriviaQ *q = &question_pool[qIndex];
        show(q->line1, q->line2, 0);

        char key = Keypad_getKey();
        if (key >= 'A' && key <= 'D') {
            lastAnswer = key;
            showingFeedback = true;
        }
    } else {
        TriviaQ *q = &question_pool[qIndex];

        if (lastAnswer == q->correct) {
            show("Correct!        ", "                ", 1000);
            correctCount++;
        } else {
            show("Wrong!          ", "                ", 1000);
            lives--;
        }

        qIndex++;
        showingFeedback = false;
    }
}
