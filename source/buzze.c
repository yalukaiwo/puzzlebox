#include "buzzer_pwm.h"

int main(void) {
    buzzer_pwm_init();

    while (1) {
        buzzer_on();
        delay_ms(2000);
        buzzer_off();
        delay_ms(2000);
    }
}
