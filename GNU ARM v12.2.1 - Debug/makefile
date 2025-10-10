################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include gecko_sdk_4.4.6/platform/service/udelay/src/subdir.mk
-include gecko_sdk_4.4.6/platform/service/system/src/subdir.mk
-include gecko_sdk_4.4.6/platform/service/sleeptimer/src/subdir.mk
-include gecko_sdk_4.4.6/platform/service/device_init/src/subdir.mk
-include gecko_sdk_4.4.6/platform/emlib/src/subdir.mk
-include gecko_sdk_4.4.6/platform/common/toolchain/src/subdir.mk
-include gecko_sdk_4.4.6/platform/common/src/subdir.mk
-include gecko_sdk_4.4.6/platform/Device/SiliconLabs/EFM32GG/Source/subdir.mk
-include gecko_sdk_4.4.6/hardware/driver/memlcd/src/memlcd_custom/subdir.mk
-include gecko_sdk_4.4.6/hardware/board/src/subdir.mk
-include autogen/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := hazikozos
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: hazikozos.axf

# Tool invocations
hazikozos.axf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "C:\0TANULMANYOK\felev7\beagyszf\nagyhazi\hazikozos\autogen\linkerfile.ld" -Wl,--no-warn-rwx-segments -Xlinker --gc-sections -Xlinker -Map="hazikozos.map" --specs=nano.specs -o hazikozos.axf -Wl,--start-group "./app.o" "./caplesense.o" "./main.o" "./segmentlcd.o" "./segmentlcd_individual.o" "./autogen/sl_board_default_init.o" "./autogen/sl_device_init_clocks.o" "./autogen/sl_event_handler.o" "./gecko_sdk_4.4.6/hardware/board/src/sl_board_control_gpio.o" "./gecko_sdk_4.4.6/hardware/board/src/sl_board_init.o" "./gecko_sdk_4.4.6/hardware/driver/memlcd/src/memlcd_custom/sl_memlcd_custom.o" "./gecko_sdk_4.4.6/platform/Device/SiliconLabs/EFM32GG/Source/startup_efm32gg.o" "./gecko_sdk_4.4.6/platform/Device/SiliconLabs/EFM32GG/Source/system_efm32gg.o" "./gecko_sdk_4.4.6/platform/common/src/sl_assert.o" "./gecko_sdk_4.4.6/platform/common/src/sl_syscalls.o" "./gecko_sdk_4.4.6/platform/common/toolchain/src/sl_memory.o" "./gecko_sdk_4.4.6/platform/emlib/src/em_acmp.o" "./gecko_sdk_4.4.6/platform/emlib/src/em_cmu.o" "./gecko_sdk_4.4.6/platform/emlib/src/em_core.o" "./gecko_sdk_4.4.6/platform/emlib/src/em_emu.o" "./gecko_sdk_4.4.6/platform/emlib/src/em_gpio.o" "./gecko_sdk_4.4.6/platform/emlib/src/em_lcd.o" "./gecko_sdk_4.4.6/platform/emlib/src/em_lesense.o" "./gecko_sdk_4.4.6/platform/emlib/src/em_msc.o" "./gecko_sdk_4.4.6/platform/emlib/src/em_rtc.o" "./gecko_sdk_4.4.6/platform/emlib/src/em_system.o" "./gecko_sdk_4.4.6/platform/emlib/src/em_timer.o" "./gecko_sdk_4.4.6/platform/emlib/src/em_vcmp.o" "./gecko_sdk_4.4.6/platform/service/device_init/src/sl_device_init_emu_s0.o" "./gecko_sdk_4.4.6/platform/service/device_init/src/sl_device_init_hfxo_s0.o" "./gecko_sdk_4.4.6/platform/service/device_init/src/sl_device_init_lfxo_s0.o" "./gecko_sdk_4.4.6/platform/service/device_init/src/sl_device_init_nvic.o" "./gecko_sdk_4.4.6/platform/service/sleeptimer/src/sl_sleeptimer.o" "./gecko_sdk_4.4.6/platform/service/sleeptimer/src/sl_sleeptimer_hal_rtc.o" "./gecko_sdk_4.4.6/platform/service/system/src/sl_system_init.o" "./gecko_sdk_4.4.6/platform/service/system/src/sl_system_process_action.o" "./gecko_sdk_4.4.6/platform/service/udelay/src/sl_udelay.o" "./gecko_sdk_4.4.6/platform/service/udelay/src/sl_udelay_armv6m_gcc.o" -lgcc -lc -lm -lnosys -Wl,--end-group -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building out file: hazikozos.out'
	arm-none-eabi-objcopy "hazikozos.axf" "hazikozos.out"
	@echo ' '

	@echo 'Building hex file: hazikozos.hex'
	arm-none-eabi-objcopy -O ihex "hazikozos.axf" "hazikozos.hex"
	@echo ' '

	@echo 'Building bin file: hazikozos.bin'
	arm-none-eabi-objcopy -O binary "hazikozos.axf" "hazikozos.bin"
	@echo ' '

	@echo 'Building s37 file: hazikozos.s37'
	arm-none-eabi-objcopy -O srec "hazikozos.axf" "hazikozos.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "hazikozos.axf" -A
	@echo ' '

# Other Targets
clean:
	-@$(foreach FILE, $(EXECUTABLES), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(OBJS), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(C_DEPS), $(shell $(RM) $(FILE)) )
	-$(RM) hazikozos.axf
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets
