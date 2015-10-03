-include ../makefile.init

RM := rm -rf *.lst *.lis *.lpp *.map

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_UPPER_DEPS)),)
-include $(C++_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(X_DEPS)),)
-include $(X_DEPS)
endif
ifneq ($(strip $(O_DEPS)),)
-include $(O_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(SRC_UPPER_DEPS)),)
-include $(SRC_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_UPPER_DEPS)),)
-include $(CPP_UPPER_DEPS)
endif
ifneq ($(strip $(OBJ_DEPS)),)
-include $(OBJ_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CC_UPPER_DEPS)),)
-include $(CC_UPPER_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_UPPER_DEPS)),)
-include $(CXX_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS += \
libSist_Op_stable.a \

LINKER_OUTPUT_OUTPUTS += \
Sist_Op_stable.x \


# All Target
all: Sist_Op_stable.mot
	@echo 'Build complete.'

# Tool invocations
Sist_Op_stable.mot: $(LINKER_OUTPUT_OUTPUTS)
	@echo 'Invoking: Objcopy'
	rl78-elf-objcopy -O srec  $(LINKER_OUTPUT_OUTPUTS)"Sist_Op_stable.mot"
	@echo 'Finished building target: $@'
	@echo

libSist_Op_stable.a: 
	@echo 'Invoking: Library Generator'
	rl78-elf-libgen --select-lib=optlib --header-files=string --compiler-options=-Os,-fdata-sections,-ffunction-sections,-falign-jumps,-fno-function-cse,-funit-at-a-time,-mmul=rl78 -o "libSist_Op_stable.a"
	@echo 'Finished building: $@'
	@echo

Sist_Op_stable.x: $(OBJS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS)
	@echo 'Invoking: Linker'
	@echo 'Building target: $@'
	rl78-elf-ld -o "Sist_Op_stable.x" -T"/home/luisp/IC/project/Sist_Op_stable/HardwareDebug/Sist_Op_stable_HardwareDebug_auto.gsi" -T"/home/luisp/IC/project/Sist_Op_stable/HardwareDebug/LinkerSubCommand.tmp" $(USER_OBJS) $(LIBS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) -M=Sist_Op_stable.map -e_PowerON_Reset -L"/home/luisp/IC/project/Sist_Op_stable/HardwareDebug" -L"/home/luisp/IC/project/4.8-GNURL78_v14.02/" --start-group -lSist_Op_stable -lgcc --end-group
	@echo 'Finished building: $@'
	@echo

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_UPPER_DEPS)$(C_DEPS)$(X_DEPS)$(O_DEPS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(SRC_DEPS)$(ASM_DEPS)$(CC_DEPS)$(LINKER_OUTPUT_OUTPUTS)$(SRC_UPPER_DEPS)$(OBJCOPY_OUTPUTTYPE_OUTPUTS)$(CPP_UPPER_DEPS)$(OBJ_DEPS)$(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS)$(CPP_DEPS)$(CC_UPPER_DEPS)$(C_UPPER_DEPS)$(CXX_UPPER_DEPS) Sist_Op_stable.mot
	@echo
	@echo 'Clean complete.'

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
