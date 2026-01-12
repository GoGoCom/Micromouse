################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/Devices/SSD1306/intf/i2c/ssd1306_i2c.c 

C_DEPS += \
./Modules/Devices/SSD1306/intf/i2c/ssd1306_i2c.d 

OBJS += \
./Modules/Devices/SSD1306/intf/i2c/ssd1306_i2c.o 


# Each subdirectory must supply rules for building sources it contributes
Modules/Devices/SSD1306/intf/i2c/%.o Modules/Devices/SSD1306/intf/i2c/%.su Modules/Devices/SSD1306/intf/i2c/%.cyclo: ../Modules/Devices/SSD1306/intf/i2c/%.c Modules/Devices/SSD1306/intf/i2c/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Drivers" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Body" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Brain" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Devices/EEPROM" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Devices/SSD1306" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Mices" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Modules-2f-Devices-2f-SSD1306-2f-intf-2f-i2c

clean-Modules-2f-Devices-2f-SSD1306-2f-intf-2f-i2c:
	-$(RM) ./Modules/Devices/SSD1306/intf/i2c/ssd1306_i2c.cyclo ./Modules/Devices/SSD1306/intf/i2c/ssd1306_i2c.d ./Modules/Devices/SSD1306/intf/i2c/ssd1306_i2c.o ./Modules/Devices/SSD1306/intf/i2c/ssd1306_i2c.su

.PHONY: clean-Modules-2f-Devices-2f-SSD1306-2f-intf-2f-i2c

