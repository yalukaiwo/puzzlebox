
#include "fsl_gpio.h"
#include "fsl_lpi2c.h"
#include "fsl_reset.h"
#include "fsl_clock.h"

#include "ssd1306.h"
#include "fsl_lpi2c.h"
#include "fsl_clock.h"
#include "fsl_reset.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "utils/delay.h"
#include <string.h>

#define I2C_BASE LPI2C0
#define I2C_CLK_FREQ CLOCK_GetFreq(kCLOCK_BusClk)

static uint8_t buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

static void SSD1306_SendCommand(uint8_t cmd) {
    uint8_t data[2] = {0x00, cmd};
    lpi2c_master_transfer_t xfer = {
        .flags = kLPI2C_TransferDefaultFlag,
        .slaveAddress = SSD1306_I2C_ADDR,
        .direction = kLPI2C_Write,
        .subaddress = 0,
        .subaddressSize = 0,
        .data = data,
        .dataSize = sizeof(data)
    };
    LPI2C_MasterTransferBlocking(I2C_BASE, &xfer);
}

void SSD1306_Init(void) {
    RESET_PeripheralReset(kLPI2C0_RST_SHIFT_RSTn);
    lpi2c_master_config_t config;
    LPI2C_MasterGetDefaultConfig(&config);
    config.baudRate_Hz = 100000U;
    LPI2C_MasterInit(I2C_BASE, &config, I2C_CLK_FREQ);
    Delay_us(100000);

    SSD1306_SendCommand(0xAE); // Display off
    SSD1306_SendCommand(0x20); // Set Memory Addressing Mode
    SSD1306_SendCommand(0x10);
    SSD1306_SendCommand(0xB0);
    SSD1306_SendCommand(0xC8);
    SSD1306_SendCommand(0x00);
    SSD1306_SendCommand(0x10);
    SSD1306_SendCommand(0x40);
    SSD1306_SendCommand(0x81);
    SSD1306_SendCommand(0xFF);
    SSD1306_SendCommand(0xA1);
    SSD1306_SendCommand(0xA6);
    SSD1306_SendCommand(0xA8);
    SSD1306_SendCommand(0x3F);
    SSD1306_SendCommand(0xA4);
    SSD1306_SendCommand(0xD3);
    SSD1306_SendCommand(0x00);
    SSD1306_SendCommand(0xD5);
    SSD1306_SendCommand(0xF0);
    SSD1306_SendCommand(0xD9);
    SSD1306_SendCommand(0x22);
    SSD1306_SendCommand(0xDA);
    SSD1306_SendCommand(0x12);
    SSD1306_SendCommand(0xDB);
    SSD1306_SendCommand(0x20);
    SSD1306_SendCommand(0x8D);
    SSD1306_SendCommand(0x14);
    SSD1306_SendCommand(0xAF); // Display on

    SSD1306_Clear();
    SSD1306_UpdateScreen();
}

void SSD1306_Clear(void) {
    memset(buffer, 0x00, sizeof(buffer));
}

void SSD1306_UpdateScreen(void) {
    for (uint8_t page = 0; page < 8; page++) {
        SSD1306_SendCommand(0xB0 + page);
        SSD1306_SendCommand(0x00);
        SSD1306_SendCommand(0x10);
        uint8_t data[129];
        data[0] = 0x40;
        memcpy(&data[1], &buffer[SSD1306_WIDTH * page], SSD1306_WIDTH);
        lpi2c_master_transfer_t xfer = {
            .flags = kLPI2C_TransferDefaultFlag,
            .slaveAddress = SSD1306_I2C_ADDR,
            .direction = kLPI2C_Write,
            .subaddress = 0,
            .subaddressSize = 0,
            .data = data,
            .dataSize = SSD1306_WIDTH + 1
        };
        LPI2C_MasterTransferBlocking(I2C_BASE, &xfer);
    }
}

void SSD1306_DrawPixel(uint8_t x, uint8_t y, uint8_t color) {
    if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) return;
    if (color) buffer[x + (y / 8) * SSD1306_WIDTH] |= (1 << (y % 8));
    else buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
}

void SSD1306_SetCursor(uint8_t x, uint8_t y) {
    cursor_x = x;
    cursor_y = y;
}


void SSD1306_Display(void) {
    SSD1306_UpdateScreen();
}

void SSD1306_WriteString(const char* str) {
    while (*str) {
        SSD1306_WriteChar(*str++);
    }
}


void SSD1306_WriteChar(char ch) {
    // Basic placeholder: just mark a pixel per character
    SSD1306_DrawPixel(cursor_x, cursor_y, 1);
    cursor_x += 6;
    if (cursor_x > SSD1306_WIDTH - 6) {
        cursor_x = 0;
        cursor_y += 8;
    }
    if (cursor_y > SSD1306_HEIGHT - 8) {
        cursor_y = 0;
    }
}
