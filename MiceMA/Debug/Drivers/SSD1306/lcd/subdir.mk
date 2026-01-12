################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SSD1306/lcd/lcd_common.c \
../Drivers/SSD1306/lcd/oled_ssd1306.c 

C_DEPS += \
./Drivers/SSD1306/lcd/lcd_common.d \
./Drivers/SSD1306/lcd/oled_ssd1306.d 

OBJS += \
./Drivers/SSD1306/lcd/lcd_common.o \
./Drivers/SSD1306/lcd/oled_ssd1306.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SSD1306/lcd/%.o Drivers/SSD1306/lcd/%.su Drivers/SSD1306/lcd/%.cyclo: ../Drivers/SSD1306/lcd/%.c Drivers/SSD1306/lcd/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers/SSD1306" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers/EEPROM" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Module" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/DrivingModule" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-SSD1306-2f-lcd

clean-Drivers-2f-SSD1306-2f-lcd:
	-$(RM) ./Drivers/SSD1306/lcd/lcd_common.cyclo ./Drivers/SSD1306/lcd/lcd_common.d ./Drivers/SSD1306/lcd/lcd_common.o ./Drivers/SSD1306/lcd/lcd_common.su ./Drivers/SSD1306/lcd/oled_ssd1306.cyclo ./Drivers/SSD1306/lcd/oled_ssd1306.d ./Drivers/SSD1306/lcd/oled_ssd1306.o ./Drivers/SSD1306/lcd/oled_ssd1306.su

.PHONY: clean-Drivers-2f-SSD1306-2f-lcd

