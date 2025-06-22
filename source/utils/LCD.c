#include "LCD.h"
#include "lpi2c0_controller_interrupt.h"

#include <stdint.h>

#define LCD_ADDR 0x27
#define ENABLE 0x04
#define BACKLIGHT 0x08

char prevRowOne[17] = {'\0'};
char prevRowTwo[17] = {'\0'};

void delay_us(unsigned int us)
{
    for (volatile unsigned int i = 0; i < us * 10; i++);
}

static void i2c_send(uint8_t data)
{
    lpi2c0_wait_busy();

    LPI2C0->MTDR = (0x04 << 8) | (LCD_ADDR << 1);  // start and address
    LPI2C0->MTDR = (0x00 << 8) | data;             // send 1 byte
    LPI2C0->MTDR = (0x02 << 8);                    // stop
}

static void LCD_pulse_enable(uint8_t data)
{
    i2c_send(data | ENABLE | BACKLIGHT);

    delay_us(1);
    i2c_send((data & ~ENABLE) | BACKLIGHT);

    delay_us(50);
}

static void LCD_write4bits(uint8_t data)
{
    i2c_send(data | BACKLIGHT);
    LCD_pulse_enable(data);
}

static void LCD_send(uint8_t data, uint8_t mode)
{
    uint8_t high = data & 0xF0;
    uint8_t low  = (data << 4) & 0xF0;
    LCD_write4bits(high | mode);
    LCD_write4bits(low | mode);
}

void LCD_send_cmd(uint8_t cmd)
{
    LCD_send(cmd, 0x00);
}

void LCD_send_data(uint8_t data)
{
    LCD_send(data, 0x01);
}

void LCD_init(void)
{
    LCD_write4bits(0x30);
    delay_us(4500);
    LCD_write4bits(0x30);
    delay_us(150);
    LCD_write4bits(0x30);
    delay_us(150);
    LCD_write4bits(0x20);
    delay_us(150);

    LCD_send_cmd(0x28);
    LCD_send_cmd(0x0C);
    LCD_send_cmd(0x06);
    LCD_send_cmd(0x01);

    delay_us(2000);
}

void LCD_send_string(const char *str)
{
    while (*str)
    {
        LCD_send_data(*str++);
    }
}

void LCD_clear(void)
{
    LCD_send_cmd(0x01);
    delay_us(2000);
}

void LCD_set_cursor(uint8_t row, uint8_t col)
{
    uint8_t row_offsets[] = {0x00, 0x40};

    if (row > 1) row = 1;
    if (col > 15) col = 15;

    LCD_send_cmd(0x80 | (col + row_offsets[row]));
}

void LCD_print(char *row1, char*row2) {
	if (!!strcmp(row1, prevRowOne)) {
		LCD_set_cursor(0,0);
		LCD_send_string(row1);
		strcpy(prevRowOne, row1);
	}

	if (!!strcmp(row2, prevRowTwo)) {
		LCD_set_cursor(1,0);
		LCD_send_string(row2);
		strcpy(prevRowOne, row2);
	}
}


