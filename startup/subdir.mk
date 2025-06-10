# Add startup_mcxa153.c build rule here
source/startup/startup_mcxa153.o: ../source/startup/startup_mcxa153.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -c -o $@ $<
