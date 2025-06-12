################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/games/game_control.c \
../source/games/gps_location.game.c \
../source/games/gps_proximity.game.c 

C_DEPS += \
./source/games/game_control.d \
./source/games/gps_location.game.d \
./source/games/gps_proximity.game.d 

OBJS += \
./source/games/game_control.o \
./source/games/gps_location.game.o \
./source/games/gps_proximity.game.o 


# Each subdirectory must supply rules for building sources it contributes
source/games/%.o: ../source/games/%.c source/games/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MCXA153VLH -DCPU_MCXA153VLH_cm33_nodsp -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=0 -DMCUX_META_BUILD -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\adibh\MCUXpressoIDE\workspace\project\source" -I"C:\Users\adibh\MCUXpressoIDE\workspace\project\CMSIS" -I"C:\Users\adibh\MCUXpressoIDE\workspace\project\CMSIS\m-profile" -I"C:\Users\adibh\MCUXpressoIDE\workspace\project\device" -I"C:\Users\adibh\MCUXpressoIDE\workspace\project\device\periph" -O0 -fno-common -g3 -gdwarf-4 -mcpu=cortex-m33+nodsp -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33+nodsp -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-games

clean-source-2f-games:
	-$(RM) ./source/games/game_control.d ./source/games/game_control.o ./source/games/gps_location.game.d ./source/games/gps_location.game.o ./source/games/gps_proximity.game.d ./source/games/gps_proximity.game.o

.PHONY: clean-source-2f-games

