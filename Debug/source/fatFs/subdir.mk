################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/fatFs/ff.c \
../source/fatFs/sdmm.c 

C_DEPS += \
./source/fatFs/ff.d \
./source/fatFs/sdmm.d 

OBJS += \
./source/fatFs/ff.o \
./source/fatFs/sdmm.o 


# Each subdirectory must supply rules for building sources it contributes
source/fatFs/%.o: ../source/fatFs/%.c source/fatFs/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MCXA153VLH -DCPU_MCXA153VLH_cm33_nodsp -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=0 -DMCUX_META_BUILD -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\adibh\MCUXpressoIDE\workspace\project\source" -I"C:\Users\adibh\MCUXpressoIDE\workspace\project\CMSIS" -I"C:\Users\adibh\MCUXpressoIDE\workspace\project\CMSIS\m-profile" -I"C:\Users\adibh\MCUXpressoIDE\workspace\project\device" -I"C:\Users\adibh\MCUXpressoIDE\workspace\project\device\periph" -I"${workspace_loc:${ProjDirPath}/device
}" -I"${workspace_loc:${ProjDirPath}/device/periph
}" -O0 -fno-common -g3 -gdwarf-4 -mcpu=cortex-m33+nodsp -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33+nodsp -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-fatFs

clean-source-2f-fatFs:
	-$(RM) ./source/fatFs/ff.d ./source/fatFs/ff.o ./source/fatFs/sdmm.d ./source/fatFs/sdmm.o

.PHONY: clean-source-2f-fatFs

