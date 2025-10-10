################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../gecko_sdk_4.4.6/hardware/driver/memlcd/src/memlcd_custom/sl_memlcd_custom.c 

OBJS += \
./gecko_sdk_4.4.6/hardware/driver/memlcd/src/memlcd_custom/sl_memlcd_custom.o 

C_DEPS += \
./gecko_sdk_4.4.6/hardware/driver/memlcd/src/memlcd_custom/sl_memlcd_custom.d 


# Each subdirectory must supply rules for building sources it contributes
gecko_sdk_4.4.6/hardware/driver/memlcd/src/memlcd_custom/sl_memlcd_custom.o: ../gecko_sdk_4.4.6/hardware/driver/memlcd/src/memlcd_custom/sl_memlcd_custom.c gecko_sdk_4.4.6/hardware/driver/memlcd/src/memlcd_custom/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFM32GG990F1024=1' '-DHFXO_FREQ=48000000' '-DSL_BOARD_NAME="BRD2200A"' '-DSL_BOARD_REV="B05"' '-DSL_COMPONENT_CATALOG_PRESENT=1' '-DMEMLCD_CUSTOM_DRIVER=1' -I"C:\0TANULMANYOK\felev7\beagyszf\nagyhazi\hazikozos\config" -I"C:\0TANULMANYOK\felev7\beagyszf\nagyhazi\hazikozos\autogen" -I"C:\0TANULMANYOK\felev7\beagyszf\nagyhazi\hazikozos" -I"C:\0TANULMANYOK\felev7\beagyszf\nagyhazi\hazikozos\gecko_sdk_4.4.6\platform\Device\SiliconLabs\EFM32GG\Include" -I"C:\0TANULMANYOK\felev7\beagyszf\nagyhazi\hazikozos\gecko_sdk_4.4.6\platform\common\inc" -I"C:\0TANULMANYOK\felev7\beagyszf\nagyhazi\hazikozos\gecko_sdk_4.4.6\hardware\board\inc" -I"C:\0TANULMANYOK\felev7\beagyszf\nagyhazi\hazikozos\gecko_sdk_4.4.6\platform\CMSIS\Core\Include" -I"C:\0TANULMANYOK\felev7\beagyszf\nagyhazi\hazikozos\gecko_sdk_4.4.6\platform\service\device_init\inc" -I"C:\0TANULMANYOK\felev7\beagyszf\nagyhazi\hazikozos\gecko_sdk_4.4.6\platform\emlib\inc" -I"C:\0TANULMANYOK\felev7\beagyszf\nagyhazi\hazikozos\gecko_sdk_4.4.6\hardware\driver\memlcd\inc" -I"C:\0TANULMANYOK\felev7\beagyszf\nagyhazi\hazikozos\gecko_sdk_4.4.6\hardware\driver\memlcd\src\memlcd_display_custom" -I"C:\0TANULMANYOK\felev7\beagyszf\nagyhazi\hazikozos\gecko_sdk_4.4.6\platform\common\toolchain\inc" -I"C:\0TANULMANYOK\felev7\beagyszf\nagyhazi\hazikozos\gecko_sdk_4.4.6\platform\service\system\inc" -I"C:\0TANULMANYOK\felev7\beagyszf\nagyhazi\hazikozos\gecko_sdk_4.4.6\platform\service\sleeptimer\inc" -I"C:\0TANULMANYOK\felev7\beagyszf\nagyhazi\hazikozos\gecko_sdk_4.4.6\platform\service\udelay\inc" -Os -Wall -Wextra -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_4.4.6/hardware/driver/memlcd/src/memlcd_custom/sl_memlcd_custom.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


