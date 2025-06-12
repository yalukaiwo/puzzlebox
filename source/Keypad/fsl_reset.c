#include "fsl_reset.h"
void RESET_SetPeripheralReset(reset_ip_name_t peripheral) {
    (void)peripheral;
}
void RESET_ClearPeripheralReset(reset_ip_name_t peripheral) {
    (void)peripheral;
}
void RESET_PeripheralReset(reset_ip_name_t peripheral) {
    RESET_SetPeripheralReset(peripheral);
    RESET_ClearPeripheralReset(peripheral);
}
