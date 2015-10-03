# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../src/reset_program.asm 

C_SRCS += \
../src/Sist_Op_stable.c \
../src/ctrdrv.c \
../src/drvADC.c \
../src/drvBot.c \
../src/drvInterrupt.c \
../src/drvLcd.c \
../src/drvLed.c \
../src/drvPID.c \
../src/drvPWM.c \
../src/drvSer.c \
../src/drvTimer.c \
../src/hardware_setup.c \
../src/interrupt_handlers.c \
../src/kernel.c \
../src/lcd_panel.c \
../src/r_cg_adc.c \
../src/r_cg_adc_user.c \
../src/r_cg_cgc.c \
../src/r_cg_intc.c \
../src/r_cg_intc_user.c \
../src/r_cg_it.c \
../src/r_cg_it_user.c \
../src/r_cg_rtc.c \
../src/r_cg_rtc_user.c \
../src/r_cg_lcd.c \
../src/r_cg_serial.c \
../src/r_cg_timer.c \
../src/r_cg_timer_user.c \
../src/r_systeminit.c \
../src/vector_table.c 


OBJS += \
./src/Sist_Op_stable.o \
./src/ctrdrv.o \
./src/drvADC.o \
./src/drvBot.o \
./src/drvInterrupt.o \
./src/drvLcd.o \
./src/drvLed.o \
./src/drvPID.o \
./src/drvPWM.o \
./src/drvSer.o \
./src/drvTimer.o \
./src/hardware_setup.o \
./src/interrupt_handlers.o \
./src/kernel.o \
./src/lcd_panel.o \
./src/r_cg_adc.o \
./src/r_cg_adc_user.o \
./src/r_cg_cgc.o \
./src/r_cg_intc.o \
./src/r_cg_intc_user.o \
./src/r_cg_it.o \
./src/r_cg_it_user.o \
./src/r_cg_rtc.o \
./src/r_cg_rtc_user.o \
./src/r_cg_lcd.o \
./src/r_cg_serial.o \
./src/r_cg_timer.o \
./src/r_cg_timer_user.o \
./src/r_systeminit.o \
./src/reset_program.o \
./src/vector_table.o 

C_DEPS += \
./src/Sist_Op_stable.d \
./src/ctrdrv.d \
./src/drvADC.d \
./src/drvBot.d \
./src/drvInterrupt.d \
./src/drvLcd.d \
./src/drvLed.d \
./src/drvPID.d \
./src/drvPWM.d \
./src/drvSer.d \
./src/drvTimer.d \
./src/hardware_setup.d \
./src/interrupt_handlers.d \
./src/kernel.d \
./src/lcd_panel.d \
./src/r_cg_adc.d \
./src/r_cg_adc_user.d \
./src/r_cg_cgc.d \
./src/r_cg_intc.d \
./src/r_cg_intc_user.d \
./src/r_cg_it.d \
./src/r_cg_it_user.d \
./src/r_cg_rtc.d \
./src/r_cg_rtc_user.d \
./src/r_cg_lcd.d \
./src/r_cg_serial.d \
./src/r_cg_timer.d \
./src/r_cg_timer_user.d \
./src/r_systeminit.d \
./src/vector_table.d 

ASM_DEPS += \
./src/reset_program.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o src/%.d: ../src/%.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	rl78-elf-gcc -MM -MP -MF "$(@:%.o=%.d)" -MT "$(@:%.o=%.d)"   -I"/home/luisp/IC/project/Sist_Op_stable" -I"/home/luisp/IC/project/optlibinc" -g3 -g -gdwarf-2 -mmul=rl78 -x c "$<"
	rl78-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" -I"/home/luisp/IC/project/optlibinc" -g3 -g -gdwarf-2 -mmul=rl78 -c -x c -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo

src/%.o src/%.d: ../src/%.asm
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	rl78-elf-gcc -MM -MP -MF "$(@:%.o=%.d)" -MT "$(@:%.o=%.d)"   -I"/home/luisp/IC/project/Sist_Op_stable" -I"/home/luisp/IC/project/optlibinc" -g2 -g -gdwarf-2 -mmul=rl78 -Wa,-gdwarf2 -x assembler-with-cpp "$<"
	rl78-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" -I"/home/luisp/IC/project/optlibinc" -g2 -g -gdwarf-2 -mmul=rl78 -Wa,-gdwarf2 -c -x assembler-with-cpp -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo
