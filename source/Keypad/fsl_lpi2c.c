
#include <Keypad/fsl_lpi2c.h>
void LPI2C_MasterGetDefaultConfig(lpi2c_master_config_t *config) {}
void LPI2C_MasterInit(LPI2C_Type *base, const lpi2c_master_config_t *config, uint32_t sourceClock_Hz) {}
status_t LPI2C_MasterTransferBlocking(LPI2C_Type *base, lpi2c_master_transfer_t *xfer) { return kStatus_Success; }
