#include "sh1122.h"
#include "lpi2c0_controller_polling.h"
#include "font5x8.h"
#include <string.h>

#define OLED_I2C_ADDR 0x3D  // I2C address for SH1122

static uint8_t framebuffer[16][256];
static uint8_t cursor_row = 0;
static uint8_t cursor_col = 0;

static void SH1122_WriteCommand(uint8_t cmd) {
    uint8_t buffer[1] = { cmd };
    lpi2c0_write_cmd(OLED_I2C_ADDR, buffer, 1);
}

static void SH1122_WriteData(uint8_t data) {
    uint8_t buffer[1] = { data };
    lpi2c0_write_data(OLED_I2C_ADDR, buffer, 1);
}

void SH1122_Init(void) {
    lpi2c0_controller_init();  // Your polling-based I2C setup

    const uint8_t init_cmds[] = {
        0xAE, 0xD5, 0x50, 0xA8, 0x3F, 0xD3, 0x00,
        0x40, 0xAD, 0x8B, 0xA1, 0xC8, 0xDA, 0x12,
        0x81, 0x7F, 0xD9, 0xF1, 0xDB, 0x40, 0xA4,
        0xA6, 0xAF
    };

    for (size_t i = 0; i < sizeof(init_cmds); i++) {
        SH1122_WriteCommand(init_cmds[i]);
    }

    SH1122_Clear();
    SH1122_Display();
}

void SH1122_Clear(void) {
    memset(framebuffer, 0x00, sizeof(framebuffer));
    cursor_row = 0;
    cursor_col = 0;
}

void SH1122_Display(void) {
    for (uint8_t page = 0; page < 16; page++) {
        SH1122_WriteCommand(0xB0 | page);  // Set page
        SH1122_WriteCommand(0x00);         // Set lower column address
        SH1122_WriteCommand(0x10);         // Set higher column address

        for (uint16_t col = 0; col < 256; col++) {
            SH1122_WriteData(framebuffer[page][col]);
        }
    }
}

void SH1122_WriteChar(char c) {
    if (c == '\n') {
        cursor_row++;
        cursor_col = 0;
        return;
    }

    if (c < 32 || c > 126) return;

    if (cursor_col + 6 >= 256) {
        cursor_row++;
        cursor_col = 0;
    }

    if (cursor_row >= 16) return;

    for (int i = 0; i < 5; i++) {
        framebuffer[cursor_row][cursor_col++] = FONTS[c - 32][i];
    }

    framebuffer[cursor_row][cursor_col++] = 0x00; // spacing
}

void SH1122_WriteString(const char* str) {
    while (*str) {
        SH1122_WriteChar(*str++);
    }
}

void SH1122_SetCursor(uint8_t row, uint8_t col) {
    if (row >= 16 || col >= 256) return;
    cursor_row = row;
    cursor_col = col;
}
