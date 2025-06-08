#ifndef SH1122_H
#define SH1122_H

#include <stdint.h>
#include <stdbool.h>

#define SH1122_ADDRESS 0x3C // I2C address
#define SH1122_WIDTH   256
#define SH1122_HEIGHT  64
#define SH1122_PAGES   (SH1122_HEIGHT / 8)

#ifdef __cplusplus
extern "C" {
#endif

void SH1122_Init(void);
void SH1122_Clear(void);
void SH1122_DrawPixel(uint8_t x, uint8_t y, bool color);
void SH1122_DrawChar(uint8_t x, uint8_t y, char c);
void SH1122_DrawText(uint8_t x, uint8_t y, const char *text);
void SH1122_UpdateScreen(void);

#ifdef __cplusplus
}
#endif

#endif // SH1122_H
