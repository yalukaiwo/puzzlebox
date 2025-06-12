################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/ctimer1_pwm.c \
../source/fifo.c \
../source/gpio_output.c \
../source/lpi2c0_controller_polling.c \
../source/lpuart0_interrupt.c \
../source/lpuart2_interrupt.c \
../source/main.c \
../source/retarget.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/ctimer1_pwm.d \
./source/fifo.d \
./source/gpio_output.d \
./source/lpi2c0_controller_polling.d \
./source/lpuart0_interrupt.d \
./source/lpuart2_interrupt.d \
./source/main.d \
./source/retarget.d \
./source/semihost_hardfault.d 

OBJS += \
./source/ctimer1_pwm.o \
./source/fifo.o \
./source/gpio_output.o \
./source/lpi2c0_controller_polling.o \
./source/lpuart0_interrupt.o \
./source/lpuart2_interrupt.o \
./source/main.o \
./source/retarget.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MCXA153VLH -DCPU_MCXA153VLH_cm33_nodsp -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=0 -DMCUX_META_BUILD -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\adibh\MCUXpressoIDE\workspace\project\source" -I"C:\Users\adibh\MCUXpressoIDE\workspace\project\CMSIS" -I"C:\Users\adibh\MCUXpressoIDE\workspace\project\CMSIS\m-profile" -I"C:\Users\adibh\MCUXpressoIDE\workspace\project\device" -I"C:\Users\adibh\MCUXpressoIDE\workspace\project\device\periph" -O0 -fno-common -g3 -gdwarf-4 -mcpu=cortex-m33+nodsp -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33+nodsp -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/ctimer1_pwm.d ./source/ctimer1_pwm.o ./source/fifo.d ./source/fifo.o ./source/gpio_output.d ./source/gpio_output.o ./source/lpi2c0_controller_polling.d ./source/lpi2c0_controller_polling.o ./source/lpuart0_interrupt.d ./source/lpuart0_interrupt.o ./source/lpuart2_interrupt.d ./source/lpuart2_interrupt.o ./source/main.d ./source/main.o ./source/retarget.d ./source/retarget.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

