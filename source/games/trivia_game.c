#include "lcdDriver/lcd.h"
#include "Keypad/keypad.h"
#include "games/game_control.h"
#include "utils/delay.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "games/trivia_game.h"

#define MAX_LIVES 3
#define TOTAL_QUESTIONS 10
#define QUIZ_SIZE 5

typedef struct {
    const char *line1;   // LCD line 1: Question
    const char *line2;   // LCD line 2: Options
    char correct;        // 'A', 'B', 'C', or 'D'
} TriviaQ;

// Question pool
static TriviaQ question_pool[] = {
    {"2+2*2=?",        "A:6 B:8 C:4 D:10", 'A'},
    {"15-4*3=?",       "A:3 B:11 C:9 D:0", 'A'},
    {"(9+3)/3=?",      "A:4 B:5 C:3 D:2", 'A'},
    {"7*2-6=?",        "A:6 B:10 C:8 D:12", 'C'},
    {"Capital USA?",   "A:DC B:NY C:TX D:LA", 'A'},
    {"Capital Japan?", "A:Os B:Tk C:Ky D:Ng", 'B'},
    {"Boil temp (C)?", "A:90 B:80 C:100 D:120", 'C'},
    {"Fast land anim?", "A:Ch B:Hr C:Tg D:Ln", 'A'},
    {"Teeth count?",   "A:28 B:30 C:32 D:36", 'C'},
    {"Has DNA?",       "A:Virus B:H2O C:Book D:Air", 'A'}
};

static void show(const char *l1, const char *l2, int delay_ms) {
    lcd_clear();
    lcd_set_cursor(0, 0); lcd_send_string(l1);
    lcd_set_cursor(1, 0); lcd_send_string(l2);
    if (delay_ms > 0) Delay_ms(delay_ms);
}

static void shuffle_questions(void) {
    for (int i = TOTAL_QUESTIONS - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        TriviaQ tmp = question_pool[i];
        question_pool[i] = question_pool[j];
        question_pool[j] = tmp;
    }
}

void Game_Trivia(game_controller_t *gc)
{
    static int qIndex = -2; // Start from intro screen
    static int correct = 0;
    static int lives = MAX_LIVES;
    static bool showingFeedback = false;
    static char lastAnswer = 0;

    if (qIndex == -2) {
        shuffle_questions();
        show("TRIVIA TIME!", "Press A/B/C/D", 1500);
        show("10 Ques", "3 lives only", 1000);
        qIndex = 0;
        return;
    }

    if (qIndex >= QUIZ_SIZE || lives == 0) {
        bool result = correct >= (QUIZ_SIZE / 2);
        gc->gameSuccessFlag = result;

        if (result) {
            GAME_STATUS_SUCCESS();
        } else {
            GAME_STATUS_FAILURE();
            Delay_ms(2000);
            gc->gameFailFlag = false;
        }

        // Reset state for next time
        qIndex = -2;
        correct = 0;
        lives = MAX_LIVES;
        showingFeedback = false;
        return;
    }

    if (!showingFeedback) {
        TriviaQ *q = &question_pool[qIndex];
        show(q->line1, q->line2, 0);

        char key = Keypad_Scan();
        if (key >= 'A' && key <= 'D') {
            lastAnswer = key;
            showingFeedback = true;
        }
    } else {
        TriviaQ *q = &question_pool[qIndex];

        if (lastAnswer == q->correct) {
            show("Correct!", "", 1000);
            GAME_STATUS_SUCCESS();
            correct++;
        } else {
            show("Wrong!", "", 1000);
            GAME_STATUS_FAILURE();
            lives--;
        }

        qIndex++;
        showingFeedback = false;
    }
}
