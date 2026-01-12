################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/Devices/EEPROM/ee.c 

C_DEPS += \
./Modules/Devices/EEPROM/ee.d 

OBJS += \
./Modules/Devices/EEPROM/ee.o 


# Each subdirectory must supply rules for building sources it contributes
Modules/Devices/EEPROM/%.o Modules/Devices/EEPROM/%.su Modules/Devices/EEPROM/%.cyclo: ../Modules/Devices/EEPROM/%.c Modules/Devices/EEPROM/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Drivers" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Body" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Brain" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Devices/EEPROM" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Devices/SSD1306" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Mices" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Modules-2f-Devices-2f-EEPROM

clean-Modules-2f-Devices-2f-EEPROM:
	-$(RM) ./Modules/Devices/EEPROM/ee.cyclo ./Modules/Devices/EEPROM/ee.d ./Modules/Devices/EEPROM/ee.o ./Modules/Devices/EEPROM/ee.su

.PHONY: clean-Modules-2f-Devices-2f-EEPROM

