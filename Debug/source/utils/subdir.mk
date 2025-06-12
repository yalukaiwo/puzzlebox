################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/utils/GPS.c \
../source/utils/Logger.c \
../source/utils/SD.c \
../source/utils/buzzer.c 

C_DEPS += \
./source/utils/GPS.d \
./source/utils/Logger.d \
./source/utils/SD.d \
./source/utils/buzzer.d 

OBJS += \
./source/utils/GPS.o \
./source/utils/Logger.o \
./source/utils/SD.o \
./source/utils/buzzer.o 


# Each subdirectory must supply rules for building sources it contributes
source/utils/%.o: ../source/utils/%.c source/utils/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MCXA153VLH -DCPU_MCXA153VLH_cm33_nodsp -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=0 -DMCUX_META_BUILD -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\adibh\MCUXpressoIDE\workspace\project\source" -I"C:\Users\adibh\MCUXpressoIDE\workspace\project\CMSIS" -I"C:\Users\adibh\MCUXpressoIDE\workspace\project\CMSIS\m-profile" -I"C:\Users\adibh\MCUXpressoIDE\workspace\project\device" -I"C:\Users\adibh\MCUXpressoIDE\workspace\project\device\periph" -O0 -fno-common -g3 -gdwarf-4 -mcpu=cortex-m33+nodsp -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33+nodsp -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-utils

clean-source-2f-utils:
	-$(RM) ./source/utils/GPS.d ./source/utils/GPS.o ./source/utils/Logger.d ./source/utils/Logger.o ./source/utils/SD.d ./source/utils/SD.o ./source/utils/buzzer.d ./source/utils/buzzer.o

.PHONY: clean-source-2f-utils

