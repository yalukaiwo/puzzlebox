/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"
#include "fsl_gpio.h"
#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The board name */
#define BOARD_NAME "FRDM-MCXA153"
/*! @brief The manufacturer name */
#define MANUFACTURER_NAME "NXP"

/*! @brief The UART to use for debug messages. */
#define BOARD_DEBUG_UART_TYPE     kSerialPort_Uart
#define BOARD_DEBUG_UART_CLK_FREQ 12000000U

#ifndef BOARD_DEBUG_UART_BAUDRATE
#define BOARD_DEBUG_UART_BAUDRATE 115200U
#endif

#define BOARD_DEBUG_UART_BASEADDR   (uint32_t) LPUART0
#define BOARD_DEBUG_UART_INSTANCE   0U
#define BOARD_DEBUG_UART_CLK_ATTACH kFRO12M_to_LPUART0
#define BOARD_DEBUG_UART_RST        kLPUART0_RST_SHIFT_RSTn
#define BOARD_DEBUG_UART_CLKSRC     kCLOCK_LPUART0
#define BOARD_UART_IRQ_HANDLER      LPUART0_IRQHandler
#define BOARD_UART_IRQ              LPUART0_IRQn

/*! @brief GPIO for LED. */
#ifndef BOARD_LED_RED_GPIO
#define BOARD_LED_RED_GPIO GPIO3
#endif
#ifndef BOARD_LED_RED_GPIO_PIN
#define BOARD_LED_RED_GPIO_PIN 12U
#endif

#ifndef BOARD_LED_GREEN_GPIO
#define BOARD_LED_GREEN_GPIO GPIO3
#endif
#ifndef BOARD_LED_GREEN_GPIO_PIN
#define BOARD_LED_GREEN_GPIO_PIN 13U
#endif

#ifndef BOARD_LED_BLUE_GPIO
#define BOARD_LED_BLUE_GPIO GPIO3
#endif
#ifndef BOARD_LED_BLUE_GPIO_PIN
#define BOARD_LED_BLUE_GPIO_PIN 0U
#endif

/*! @brief Keypad Configuration (Added) */
#define KEYPAD_ROW_PORT          GPIOA
#define KEYPAD_ROW_PINS          {0, 1, 2, 3}  // PTA0-PTA3 (Rows 1-4)
#define KEYPAD_COL_PORT          GPIOA
#define KEYPAD_COL_PINS          {4, 5, 6, 7}  // PTA4-PTA7 (Columns 1-4)
#define KEYPAD_PULLUPS_ENABLE    1

/*! @brief OLED Configuration (Added) */
#define OLED_I2C                 I2C0
#define OLED_I2C_CLOCK_SOURCE    kCLOCK_I2c0
#define OLED_I2C_BAUDRATE        400000       // 400kHz
#define OLED_I2C_ADDRESS         0x3C         // Default SSD1306 address

/*! @brief GPIO pull-up helper (Added) */
#define GPIO_PORT_ENABLE_PULLUP(port, mask) \
    (port->PUP = ((port->PUP & ~(mask)) | (mask))

/*! @brief GPIO for SW. */
#ifndef BOARD_SW2_GPIO
#define BOARD_SW2_GPIO GPIO3
#endif
#ifndef BOARD_SW2_GPIO_PIN
#define BOARD_SW2_GPIO_PIN 29U
#endif
#define BOARD_SW2_NAME        "SW2"
#define BOARD_SW2_IRQ         GPIO3_IRQn
#define BOARD_SW2_IRQ_HANDLER GPIO3_IRQHandler

#ifndef BOARD_SW3_GPIO
#define BOARD_SW3_GPIO GPIO1
#endif
#ifndef BOARD_SW3_GPIO_PIN
#define BOARD_SW3_GPIO_PIN 7U
#endif
#define BOARD_SW3_NAME        "SW3"
#define BOARD_SW3_IRQ         GPIO1_IRQn
#define BOARD_SW3_IRQ_HANDLER GPIO1_IRQHandler

/* Board LED color mapping */
#define LOGIC_LED_ON  0U
#define LOGIC_LED_OFF 1U

/*! @brief Game Status Indicators (Added) */
#define GAME_STATUS_SUCCESS()   LED_GREEN_ON()
#define GAME_STATUS_FAILURE()   LED_RED_ON()
#define GAME_STATUS_WAITING()   LED_BLUE_TOGGLE()

#define LED_RED_INIT(output)                                           \
    GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, output); \
    BOARD_LED_RED_GPIO->PDDR |= (1U << BOARD_LED_RED_GPIO_PIN)
#define LED_RED_ON() \
    GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, LOGIC_LED_ON)
#define LED_RED_OFF() \
    GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, LOGIC_LED_OFF)
#define LED_RED_TOGGLE() \
    GPIO_PortToggle(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN)

#define LED_GREEN_INIT(output)                                             \
    GPIO_PinWrite(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, output); \
    BOARD_LED_GREEN_GPIO->PDDR |= (1U << BOARD_LED_GREEN_GPIO_PIN)
#define LED_GREEN_ON() \
    GPIO_PinWrite(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, LOGIC_LED_ON)
#define LED_GREEN_OFF() \
    GPIO_PinWrite(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, LOGIC_LED_OFF)
#define LED_GREEN_TOGGLE() \
    GPIO_PortToggle(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN)

#define LED_BLUE_INIT(output)                                            \
    GPIO_PinWrite(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, output); \
    BOARD_LED_BLUE_GPIO->PDDR |= (1U << BOARD_LED_BLUE_GPIO_PIN)
#define LED_BLUE_ON() \
    GPIO_PinWrite(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, LOGIC_LED_ON)
#define LED_BLUE_OFF() \
    GPIO_PinWrite(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, LOGIC_LED_OFF)
#define LED_BLUE_TOGGLE() \
    GPIO_PortToggle(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN)

/*******************************************************************************
 * API
 ******************************************************************************/
void BOARD_InitDebugConsole(void);

#endif /* _BOARD_H_ */
