################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/libmcp3204/Core/Src/libmcp3204.c 

OBJS += \
./Libraries/libmcp3204/Core/Src/libmcp3204.o 

C_DEPS += \
./Libraries/libmcp3204/Core/Src/libmcp3204.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/libmcp3204/Core/Src/%.o Libraries/libmcp3204/Core/Src/%.su: ../Libraries/libmcp3204/Core/Src/%.c Libraries/libmcp3204/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/sanlu/Documents/Uni/Year 3/Sem 1/Rocketry/gc-logger/DataLogger/Libraries/libmcp3204/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-libmcp3204-2f-Core-2f-Src

clean-Libraries-2f-libmcp3204-2f-Core-2f-Src:
	-$(RM) ./Libraries/libmcp3204/Core/Src/libmcp3204.d ./Libraries/libmcp3204/Core/Src/libmcp3204.o ./Libraries/libmcp3204/Core/Src/libmcp3204.su

.PHONY: clean-Libraries-2f-libmcp3204-2f-Core-2f-Src

