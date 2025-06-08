#include "oled_ui.h"
#include "sh1122.h"
#include <string.h>

void OLED_Init(void) {
    SH1122_Init();
}

void OLED_Clear(void) {
    SH1122_Clear();
    SH1122_Display();
}

void OLED_ShowMessage(const char* line1, const char* line2) {
    SH1122_Clear();
    SH1122_SetCursor(0, 0);
    SH1122_WriteString(line1);
    SH1122_SetCursor(1, 0);
    SH1122_WriteString(line2);
    SH1122_Display();
}

void OLED_ShowCodeScreen(const char* code) {
    SH1122_Clear();
    SH1122_SetCursor(0, 0);
    SH1122_WriteString("Enter Code:");
    SH1122_SetCursor(1, 0);
    SH1122_WriteString(code);
    SH1122_Display();
}

void OLED_ShowQuestionScreen(const char* qline1, const char* qline2,
                              const char* optionA, const char* optionB,
                              const char* optionC, const char* optionD) {
    SH1122_Clear();

    SH1122_SetCursor(0, 0);
    SH1122_WriteString(qline1);

    SH1122_SetCursor(1, 0);
    SH1122_WriteString(qline2);

    SH1122_SetCursor(2, 0);
    SH1122_WriteString("A: ");
    SH1122_WriteString(optionA);
    SH1122_WriteString("  B: ");
    SH1122_WriteString(optionB);

    SH1122_SetCursor(3, 0);
    SH1122_WriteString("C: ");
    SH1122_WriteString(optionC);
    SH1122_WriteString("  D: ");
    SH1122_WriteString(optionD);

    SH1122_Display();
}
