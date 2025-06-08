/*!
 * \brief     Low-Power I2C controller polling (Updated for SH1122)
 * \file      lpi2c0_controller_polling.c
 * \author    Rewritten by Safin
 * \date      June 2025
 */

#include "lpi2c0_controller_polling.h"

#define I2C_TIMEOUT 10000U

static inline void lpi2c0_wait_busy(void);
static inline bool lpi2c0_txfifo_full(void);

void lpi2c0_controller_init(void)
{
    // Clock source: FRO_HF_DIV
    MRCC0->MRCC_LPI2C0_CLKSEL = MRCC_MRCC_LPI2C0_CLKSEL_MUX(2);
    MRCC0->MRCC_LPI2C0_CLKDIV = 0; // Divider = 1

    // Enable clocks
    MRCC0->MRCC_GLB_CC0_SET = MRCC_MRCC_GLB_CC0_LPI2C0(1);
    MRCC0->MRCC_GLB_CC0_SET = MRCC_MRCC_GLB_CC0_PORT1(1);

    // Release reset
    MRCC0->MRCC_GLB_RST0_SET = MRCC_MRCC_GLB_RST0_LPI2C0(1);
    MRCC0->MRCC_GLB_RST0_SET = MRCC_MRCC_GLB_RST0_PORT1(1);

    // Configure P1_8 (SDA) and P1_9 (SCL)
    PORT1->PCR[8] = PORT_PCR_LK(1) | PORT_PCR_MUX(3) |
                    PORT_PCR_PE(1) | PORT_PCR_PS(1) |
                    PORT_PCR_ODE(1) | PORT_PCR_IBE(1);
    PORT1->PCR[9] = PORT_PCR_LK(1) | PORT_PCR_MUX(3) |
                    PORT_PCR_PE(1) | PORT_PCR_PS(1) |
                    PORT_PCR_ODE(1) | PORT_PCR_IBE(1);

    LPI2C0->MCFGR1 = LPI2C_MCFGR1_PRESCALE(0);
    LPI2C0->MCFGR2 = LPI2C_MCFGR2_FILTSDA(1) | LPI2C_MCFGR2_FILTSCL(1);

    // 400 kHz I2C Fast-mode timing
    LPI2C0->MCCR0 = LPI2C_MCCR0_DATAVD(0x0F) | LPI2C_MCCR0_SETHOLD(0x1D) |
                    LPI2C_MCCR0_CLKHI(0x35) | LPI2C_MCCR0_CLKLO(0x3E);

    LPI2C0->MCR |= LPI2C_MCR_MEN(1);
}

bool lpi2c0_write_cmd(const uint8_t address, const uint8_t *cmd, const uint32_t n)
{
    lpi2c0_wait_busy();
    LPI2C0->MSR = 0xFFFFFFFF; // Clear all status flags

    LPI2C0->MTDR = LPI2C_MTDR_CMD(0b100) | LPI2C_MTDR_DATA(address);
    while (lpi2c0_txfifo_full());

    LPI2C0->MTDR = LPI2C_MTDR_CMD(0b000) | LPI2C_MTDR_DATA(0x00); // Control byte

    for (uint32_t i = 0; i < n; ++i) {
        uint32_t timeout = I2C_TIMEOUT;
        while (lpi2c0_txfifo_full() && --timeout);
        if (timeout == 0) return false;

        LPI2C0->MTDR = LPI2C_MTDR_CMD(0b000) | LPI2C_MTDR_DATA(cmd[i]);
    }

    while (lpi2c0_txfifo_full());
    LPI2C0->MTDR = LPI2C_MTDR_CMD(0b010); // STOP

    return true;
}

bool lpi2c0_write_data(const uint8_t address, const uint8_t *data, const uint32_t n)
{
    lpi2c0_wait_busy();
    LPI2C0->MSR = 0xFFFFFFFF; // Clear all status flags

    LPI2C0->MTDR = LPI2C_MTDR_CMD(0b100) | LPI2C_MTDR_DATA(address);
    while (lpi2c0_txfifo_full());

    LPI2C0->MTDR = LPI2C_MTDR_CMD(0b000) | LPI2C_MTDR_DATA(0x40); // Data control byte

    for (uint32_t i = 0; i < n; ++i) {
        uint32_t timeout = I2C_TIMEOUT;
        while (lpi2c0_txfifo_full() && --timeout);
        if (timeout == 0) return false;

        LPI2C0->MTDR = LPI2C_MTDR_CMD(0b000) | LPI2C_MTDR_DATA(data[i]);
    }

    while (lpi2c0_txfifo_full());
    LPI2C0->MTDR = LPI2C_MTDR_CMD(0b010); // STOP

    return true;
}

static inline void lpi2c0_wait_busy(void)
{
    while ((LPI2C0->MSR & (LPI2C_MSR_BBF_MASK | LPI2C_MSR_MBF_MASK)) != 0) {}
}

static inline bool lpi2c0_txfifo_full(void)
{
    uint32_t n = (LPI2C0->MFSR & LPI2C_MFSR_TXCOUNT_MASK) >> LPI2C_MFSR_TXCOUNT_SHIFT;
    return n == 4; // FIFO holds 4 words max
}
