################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../autogen/sl_board_default_init.c \
../autogen/sl_device_init_clocks.c \
../autogen/sl_event_handler.c 

OBJS += \
./autogen/sl_board_default_init.o \
./autogen/sl_device_init_clocks.o \
./autogen/sl_event_handler.o 

C_DEPS += \
./autogen/sl_board_default_init.d \
./autogen/sl_device_init_clocks.d \
./autogen/sl_event_handler.d 


# Each subdirectory must supply rules for building sources it contributes
autogen/sl_board_default_init.o: ../autogen/sl_board_default_init.c autogen/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' '-DHFXO_FREQ=48000000' '-DSL_BOARD_NAME="BRD2200A"' '-DSL_BOARD_REV="B05"' '-DSL_COMPONENT_CATALOG_PRESENT=1' '-DMEMLCD_CUSTOM_DRIVER=1' -I"C:\beagyszoftver2025\hazifeladatkozos\config" -I"C:\beagyszoftver2025\hazifeladatkozos\autogen" -I"C:\beagyszoftver2025\hazifeladatkozos" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\Device\SiliconLabs\EFM32GG\Include" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\common\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\hardware\board\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\CMSIS\Core\Include" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\service\device_init\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\emlib\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\hardware\driver\memlcd\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\common\toolchain\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\service\system\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\service\sleeptimer\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\service\udelay\inc" -Os -Wall -Wextra -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"autogen/sl_board_default_init.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

autogen/sl_device_init_clocks.o: ../autogen/sl_device_init_clocks.c autogen/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' '-DHFXO_FREQ=48000000' '-DSL_BOARD_NAME="BRD2200A"' '-DSL_BOARD_REV="B05"' '-DSL_COMPONENT_CATALOG_PRESENT=1' '-DMEMLCD_CUSTOM_DRIVER=1' -I"C:\beagyszoftver2025\hazifeladatkozos\config" -I"C:\beagyszoftver2025\hazifeladatkozos\autogen" -I"C:\beagyszoftver2025\hazifeladatkozos" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\Device\SiliconLabs\EFM32GG\Include" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\common\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\hardware\board\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\CMSIS\Core\Include" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\service\device_init\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\emlib\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\hardware\driver\memlcd\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\common\toolchain\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\service\system\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\service\sleeptimer\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\service\udelay\inc" -Os -Wall -Wextra -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"autogen/sl_device_init_clocks.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

autogen/sl_event_handler.o: ../autogen/sl_event_handler.c autogen/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' '-DHFXO_FREQ=48000000' '-DSL_BOARD_NAME="BRD2200A"' '-DSL_BOARD_REV="B05"' '-DSL_COMPONENT_CATALOG_PRESENT=1' '-DMEMLCD_CUSTOM_DRIVER=1' -I"C:\beagyszoftver2025\hazifeladatkozos\config" -I"C:\beagyszoftver2025\hazifeladatkozos\autogen" -I"C:\beagyszoftver2025\hazifeladatkozos" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\Device\SiliconLabs\EFM32GG\Include" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\common\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\hardware\board\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\CMSIS\Core\Include" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\service\device_init\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\emlib\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\hardware\driver\memlcd\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\common\toolchain\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\service\system\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\service\sleeptimer\inc" -I"C:\beagyszoftver2025\hazifeladatkozos\gecko_sdk_4.4.6\platform\service\udelay\inc" -Os -Wall -Wextra -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"autogen/sl_event_handler.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


