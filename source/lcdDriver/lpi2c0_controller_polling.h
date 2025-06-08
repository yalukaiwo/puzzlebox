/*!
 * \brief     Low-Power I2C controller polling header (for SH1122 OLED)
 * \file      lpi2c0_controller_polling.h
 * \author    Rewritten by safin
 * \date      June 2025
 */

#ifndef LPI2C0_CONTROLLER_POLLING_H
#define LPI2C0_CONTROLLER_POLLING_H

#include <MCXA153.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes the I2C0 controller and configures P1.8 and P1.9 for OLED communication.
 */
void lpi2c0_controller_init(void);

/**
 * @brief Writes a sequence of command bytes to the SH1122 OLED over I2C.
 *
 * @param address The 7-bit I2C address of the OLED (usually 0x3C).
 * @param cmd     Pointer to an array of command bytes.
 * @param n       Number of bytes to send.
 * @return true if transfer was successful, false on timeout or error.
 */
bool lpi2c0_write_cmd(const uint8_t address, const uint8_t *cmd, const uint32_t n);

/**
 * @brief Writes a sequence of display data bytes to the SH1122 OLED over I2C.
 *
 * @param address The 7-bit I2C address of the OLED (usually 0x3C).
 * @param data    Pointer to an array of data bytes.
 * @param n       Number of bytes to send.
 * @return true if transfer was successful, false on timeout or error.
 */
bool lpi2c0_write_data(const uint8_t address, const uint8_t *data, const uint32_t n);

#ifdef __cplusplus
}
#endif

#endif // LPI2C0_CONTROLLER_POLLING_H
