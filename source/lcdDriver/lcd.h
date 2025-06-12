#ifndef _LCD_H_
#define _LCD_H_

#include <stdint.h>

#define LCD_ADDR 0x27

void lcd_init(void);
void lcd_clear(void);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_print(const char *str);  // <-- alias for lcd_send_string

void lcd_send_cmd(uint8_t cmd);
void lcd_send_data(uint8_t data);
void lcd_send_string(const char *str);
void delay_us(unsigned int us);

#endif // _LCD_H_
