################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/Devices/SSD1306/lcd/lcd_common.c \
../Modules/Devices/SSD1306/lcd/oled_ssd1306.c 

C_DEPS += \
./Modules/Devices/SSD1306/lcd/lcd_common.d \
./Modules/Devices/SSD1306/lcd/oled_ssd1306.d 

OBJS += \
./Modules/Devices/SSD1306/lcd/lcd_common.o \
./Modules/Devices/SSD1306/lcd/oled_ssd1306.o 


# Each subdirectory must supply rules for building sources it contributes
Modules/Devices/SSD1306/lcd/%.o Modules/Devices/SSD1306/lcd/%.su Modules/Devices/SSD1306/lcd/%.cyclo: ../Modules/Devices/SSD1306/lcd/%.c Modules/Devices/SSD1306/lcd/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Drivers" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Body" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Brain" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Devices/EEPROM" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Devices/SSD1306" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Mices" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Modules-2f-Devices-2f-SSD1306-2f-lcd

clean-Modules-2f-Devices-2f-SSD1306-2f-lcd:
	-$(RM) ./Modules/Devices/SSD1306/lcd/lcd_common.cyclo ./Modules/Devices/SSD1306/lcd/lcd_common.d ./Modules/Devices/SSD1306/lcd/lcd_common.o ./Modules/Devices/SSD1306/lcd/lcd_common.su ./Modules/Devices/SSD1306/lcd/oled_ssd1306.cyclo ./Modules/Devices/SSD1306/lcd/oled_ssd1306.d ./Modules/Devices/SSD1306/lcd/oled_ssd1306.o ./Modules/Devices/SSD1306/lcd/oled_ssd1306.su

.PHONY: clean-Modules-2f-Devices-2f-SSD1306-2f-lcd

