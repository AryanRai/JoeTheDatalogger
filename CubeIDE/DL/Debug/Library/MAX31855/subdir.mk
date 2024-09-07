################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/MAX31855/MAX31855.c 

OBJS += \
./Library/MAX31855/MAX31855.o 

C_DEPS += \
./Library/MAX31855/MAX31855.d 


# Each subdirectory must supply rules for building sources it contributes
Library/MAX31855/%.o Library/MAX31855/%.su Library/MAX31855/%.cyclo: ../Library/MAX31855/%.c Library/MAX31855/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/buzza/STM32CubeIDE/workspace_1.14.1/DL/Library/MAX31855" -I"C:/Users/buzza/STM32CubeIDE/workspace_1.14.1/DL/Library/MPU3204" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Library-2f-MAX31855

clean-Library-2f-MAX31855:
	-$(RM) ./Library/MAX31855/MAX31855.cyclo ./Library/MAX31855/MAX31855.d ./Library/MAX31855/MAX31855.o ./Library/MAX31855/MAX31855.su

.PHONY: clean-Library-2f-MAX31855

