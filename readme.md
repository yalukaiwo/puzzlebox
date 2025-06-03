REVERSE GEOCACHE PUZZLE BOX PROJECT
===================================

OVERVIEW
--------
A microcontroller-based puzzle box requiring users to:
1. Memorize a 4-digit code (8-second display)
2. Answer 6 trivia questions (3 lives)
3. Enter correct code to unlock
Integrated with GPS functionality from team members.

HARDWARE REQUIREMENTS
---------------------
- FRDM-MCXA153 development board
- 0.91" OLED display (128x32, I2C)
- 4x4 matrix keypad
- USB Type-C cable
- GPS module (external team implementation)

CONNECTIONS
-----------
OLED Display:
- SDA -> PTE0 (I2C0_SDA)
- SCL -> PTE1 (I2C0_SCL)

Keypad:
- Rows -> PTA0-PTA3 (GPIOA0-A3)
- Columns -> PTA4-PTA7 (GPIOA4-A7)

LED Indicators:
- Red: P3_12 | Green: P3_13 | Blue: P3_0

SOFTWARE SETUP
--------------
1. Install MCUXpresso IDE v11.9+
2. Import project:
   File -> Import -> Existing Projects into Workspace
3. Build configuration:
   - Select FRDM-MCXA153 SDK
   - Build in Release mode
4. Flash to board using CMSIS-DAP debugger

GAME PLAY INSTRUCTIONS
----------------------
1. Power On:
   - OLED shows "INITIALIZING..."
   - Blue LED blinks during GPS sync

2. Code Memory Challenge:
   - 4-digit code displayed with 8s countdown
   - Example: "CODE: 4281 | TIME: 5"

3. Trivia Quiz:
   - 6 random questions from 25-question pool
   - 3 heart icons (lose 1 per wrong answer)
   - Example display:
     "CAPITAL OF FRANCE?
      A: LONDON  B: PARIS
      C: BERLIN  D: MADRID"

4. Final Unlock:
   - Enter memorized code via keypad
   - Press # to submit
   - Success: Green LED + "UNLOCKED!" display
   - Failure: Red LED + 2s cooldown

CUSTOMIZATION
-------------
To modify behavior, edit these files:

1. Change questions:
   /source/trivia/trivia.c
   (Update question_pool array)

2. Adjust lives/timeouts:
   /source/trivia/trivia.h
   #define MAX_LIVES 5
   #define QUIZ_SIZE 8

3. Modify code display time:
   /source/main.c
   Change 'for(uint8_t t = 8; t > 0; t--)'

4. Update hardware pins:
   /board/board.h
   KEYPAD_ROW_PINS / OLED_I2C

TROUBLESHOOTING
---------------
NO OLED DISPLAY:
1. Check I2C connections
2. Verify 0x3C address in board.h
3. Test with I2C scanner utility

KEYPAD NOT WORKING:
1. Confirm GPIO mappings in board.h
2. Enable internal pull-ups:
   #define KEYPAD_PULLUPS_ENABLE 1

CODE VALIDATION FAILS:
1. Check RNG initialization in generated_code.c
2. Verify ADC seed generation

REFERENCES
----------
- MCX A153 Reference Manual (NXP Doc: MCXAP64M96FS3RM)
- SSD1306 OLED Datasheet
- 4x4 Matrix Keypad Spec Sheet
- Project GitHub: [insert your repo link]