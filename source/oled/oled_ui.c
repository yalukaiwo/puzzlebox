#include "oled_ui.h"
#include "ssd1306.h"
#include <string.h>

void OLED_Init(void) {
    SSD1306_Init();
    SSD1306_Clear();
    SSD1306_Display();
}

void OLED_Clear(void) {
    SSD1306_Clear();
    SSD1306_Display();
}

void OLED_ShowMessage(const char* line1, const char* line2) {
    SSD1306_Clear();
    SSD1306_WriteString(line1);
    SSD1306_WriteChar('\n');
    SSD1306_WriteString(line2);
    SSD1306_Display();
}

void OLED_ShowCodeScreen(const char* code) {
    SSD1306_Clear();
    SSD1306_WriteString("Enter Code:");
    SSD1306_WriteChar('\n');
    SSD1306_WriteString(code);
    SSD1306_Display();
}

void OLED_ShowQuestionScreen(const char* question, const char* optionA, const char* optionB) {
    SSD1306_Clear();
    SSD1306_WriteString(question);
    SSD1306_WriteChar('\n');
    SSD1306_WriteString("A: ");
    SSD1306_WriteString(optionA);
    SSD1306_WriteChar('\n');
    SSD1306_WriteString("B: ");
    SSD1306_WriteString(optionB);
    SSD1306_Display();
}
