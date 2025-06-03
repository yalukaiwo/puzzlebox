#ifndef OLED_UI_H_
#define OLED_UI_H_

void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowMessage(const char* line1, const char* line2);
void OLED_ShowCodeScreen(const char* code);
void OLED_ShowQuestionScreen(const char* question, const char* optionA, const char* optionB);

#endif
