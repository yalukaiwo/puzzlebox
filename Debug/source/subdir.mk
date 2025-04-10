################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/fifo.c \
../source/lpuart0_interrupt.c \
../source/lpuart2_interrupt.c \
../source/main.c \
../source/retarget.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/fifo.d \
./source/lpuart0_interrupt.d \
./source/lpuart2_interrupt.d \
./source/main.d \
./source/retarget.d \
./source/semihost_hardfault.d 

OBJS += \
./source/fifo.o \
./source/lpuart0_interrupt.o \
./source/lpuart2_interrupt.o \
./source/main.o \
./source/retarget.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MCXA153VLH -DCPU_MCXA153VLH_cm33_nodsp -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=0 -DMCUX_META_BUILD -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"/Users/yalukaiwo/Documents/MCUXpressoIDE_24.12.148/workspace/project/source" -I"/Users/yalukaiwo/Documents/MCUXpressoIDE_24.12.148/workspace/project/CMSIS" -I"/Users/yalukaiwo/Documents/MCUXpressoIDE_24.12.148/workspace/project/CMSIS/m-profile" -I"/Users/yalukaiwo/Documents/MCUXpressoIDE_24.12.148/workspace/project/device" -I"/Users/yalukaiwo/Documents/MCUXpressoIDE_24.12.148/workspace/project/device/periph" -O0 -fno-common -g3 -gdwarf-4 -mcpu=cortex-m33+nodsp -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33+nodsp -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/fifo.d ./source/fifo.o ./source/lpuart0_interrupt.d ./source/lpuart0_interrupt.o ./source/lpuart2_interrupt.d ./source/lpuart2_interrupt.o ./source/main.d ./source/main.o ./source/retarget.d ./source/retarget.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

