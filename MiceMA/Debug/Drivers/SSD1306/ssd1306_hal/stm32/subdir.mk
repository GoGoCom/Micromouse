################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SSD1306/ssd1306_hal/stm32/platform.c 

C_DEPS += \
./Drivers/SSD1306/ssd1306_hal/stm32/platform.d 

OBJS += \
./Drivers/SSD1306/ssd1306_hal/stm32/platform.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SSD1306/ssd1306_hal/stm32/%.o Drivers/SSD1306/ssd1306_hal/stm32/%.su Drivers/SSD1306/ssd1306_hal/stm32/%.cyclo: ../Drivers/SSD1306/ssd1306_hal/stm32/%.c Drivers/SSD1306/ssd1306_hal/stm32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers/SSD1306" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers/EEPROM" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Module" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/DrivingModule" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-SSD1306-2f-ssd1306_hal-2f-stm32

clean-Drivers-2f-SSD1306-2f-ssd1306_hal-2f-stm32:
	-$(RM) ./Drivers/SSD1306/ssd1306_hal/stm32/platform.cyclo ./Drivers/SSD1306/ssd1306_hal/stm32/platform.d ./Drivers/SSD1306/ssd1306_hal/stm32/platform.o ./Drivers/SSD1306/ssd1306_hal/stm32/platform.su

.PHONY: clean-Drivers-2f-SSD1306-2f-ssd1306_hal-2f-stm32

