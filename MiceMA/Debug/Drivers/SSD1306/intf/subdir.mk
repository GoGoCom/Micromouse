################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SSD1306/intf/ssd1306_interface.c 

C_DEPS += \
./Drivers/SSD1306/intf/ssd1306_interface.d 

OBJS += \
./Drivers/SSD1306/intf/ssd1306_interface.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SSD1306/intf/%.o Drivers/SSD1306/intf/%.su Drivers/SSD1306/intf/%.cyclo: ../Drivers/SSD1306/intf/%.c Drivers/SSD1306/intf/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers/SSD1306" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers/EEPROM" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Module" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/DrivingModule" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-SSD1306-2f-intf

clean-Drivers-2f-SSD1306-2f-intf:
	-$(RM) ./Drivers/SSD1306/intf/ssd1306_interface.cyclo ./Drivers/SSD1306/intf/ssd1306_interface.d ./Drivers/SSD1306/intf/ssd1306_interface.o ./Drivers/SSD1306/intf/ssd1306_interface.su

.PHONY: clean-Drivers-2f-SSD1306-2f-intf

