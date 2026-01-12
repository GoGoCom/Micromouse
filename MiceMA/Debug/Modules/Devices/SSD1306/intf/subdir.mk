################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/Devices/SSD1306/intf/ssd1306_interface.c 

C_DEPS += \
./Modules/Devices/SSD1306/intf/ssd1306_interface.d 

OBJS += \
./Modules/Devices/SSD1306/intf/ssd1306_interface.o 


# Each subdirectory must supply rules for building sources it contributes
Modules/Devices/SSD1306/intf/%.o Modules/Devices/SSD1306/intf/%.su Modules/Devices/SSD1306/intf/%.cyclo: ../Modules/Devices/SSD1306/intf/%.c Modules/Devices/SSD1306/intf/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Drivers" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Body" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Brain" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Devices/EEPROM" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Devices/SSD1306" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Mices" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Modules-2f-Devices-2f-SSD1306-2f-intf

clean-Modules-2f-Devices-2f-SSD1306-2f-intf:
	-$(RM) ./Modules/Devices/SSD1306/intf/ssd1306_interface.cyclo ./Modules/Devices/SSD1306/intf/ssd1306_interface.d ./Modules/Devices/SSD1306/intf/ssd1306_interface.o ./Modules/Devices/SSD1306/intf/ssd1306_interface.su

.PHONY: clean-Modules-2f-Devices-2f-SSD1306-2f-intf

