
#include "games/game_control.h"
#include "games/trivia.h"
#include "utils/delay.h"
#include <stdbool.h>

void Game_Trivia(game_controller_t *gc)
{
    bool result = Trivia_RunGame();
    gc->gameSuccessFlag = result;

    if (result) {
        GAME_STATUS_SUCCESS();
    } else {
        GAME_STATUS_FAILURE();
        Delay_ms(2000);
        gc->gameFailFlag = false;
    }
}
