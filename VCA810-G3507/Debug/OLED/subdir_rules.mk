################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
OLED/%.o: ../OLED/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"E:/ti/ccstheia141/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/Marti/workspace_ccstheia/gpio_software_poll_LP_MSPM0G3507_nortos_ticlang" -I"C:/Users/Marti/workspace_ccstheia/gpio_software_poll_LP_MSPM0G3507_nortos_ticlang/OLED" -I"C:/Users/Marti/workspace_ccstheia/gpio_software_poll_LP_MSPM0G3507_nortos_ticlang/Debug" -I"E:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"E:/ti/mspm0_sdk_2_01_00_03/source" -gdwarf-3 -MMD -MP -MF"OLED/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


