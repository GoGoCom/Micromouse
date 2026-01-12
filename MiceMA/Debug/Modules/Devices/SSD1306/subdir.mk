################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Modules/Devices/SSD1306/nano_gfx.cpp \
../Modules/Devices/SSD1306/sova.cpp \
../Modules/Devices/SSD1306/sprite_pool.cpp \
../Modules/Devices/SSD1306/ssd1306_console.cpp 

C_SRCS += \
../Modules/Devices/SSD1306/ssd1306_16bit.c \
../Modules/Devices/SSD1306/ssd1306_1bit.c \
../Modules/Devices/SSD1306/ssd1306_8bit.c \
../Modules/Devices/SSD1306/ssd1306_fonts.c \
../Modules/Devices/SSD1306/ssd1306_generic.c \
../Modules/Devices/SSD1306/ssd1306_menu.c 

C_DEPS += \
./Modules/Devices/SSD1306/ssd1306_16bit.d \
./Modules/Devices/SSD1306/ssd1306_1bit.d \
./Modules/Devices/SSD1306/ssd1306_8bit.d \
./Modules/Devices/SSD1306/ssd1306_fonts.d \
./Modules/Devices/SSD1306/ssd1306_generic.d \
./Modules/Devices/SSD1306/ssd1306_menu.d 

OBJS += \
./Modules/Devices/SSD1306/nano_gfx.o \
./Modules/Devices/SSD1306/sova.o \
./Modules/Devices/SSD1306/sprite_pool.o \
./Modules/Devices/SSD1306/ssd1306_16bit.o \
./Modules/Devices/SSD1306/ssd1306_1bit.o \
./Modules/Devices/SSD1306/ssd1306_8bit.o \
./Modules/Devices/SSD1306/ssd1306_console.o \
./Modules/Devices/SSD1306/ssd1306_fonts.o \
./Modules/Devices/SSD1306/ssd1306_generic.o \
./Modules/Devices/SSD1306/ssd1306_menu.o 

CPP_DEPS += \
./Modules/Devices/SSD1306/nano_gfx.d \
./Modules/Devices/SSD1306/sova.d \
./Modules/Devices/SSD1306/sprite_pool.d \
./Modules/Devices/SSD1306/ssd1306_console.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/Devices/SSD1306/%.o Modules/Devices/SSD1306/%.su Modules/Devices/SSD1306/%.cyclo: ../Modules/Devices/SSD1306/%.cpp Modules/Devices/SSD1306/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Drivers" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Body" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Brain" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Devices/EEPROM" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Devices/SSD1306" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Mices" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Modules/Devices/SSD1306/%.o Modules/Devices/SSD1306/%.su Modules/Devices/SSD1306/%.cyclo: ../Modules/Devices/SSD1306/%.c Modules/Devices/SSD1306/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Drivers" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Body" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Brain" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Devices/EEPROM" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Devices/SSD1306" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Mices" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Modules-2f-Devices-2f-SSD1306

clean-Modules-2f-Devices-2f-SSD1306:
	-$(RM) ./Modules/Devices/SSD1306/nano_gfx.cyclo ./Modules/Devices/SSD1306/nano_gfx.d ./Modules/Devices/SSD1306/nano_gfx.o ./Modules/Devices/SSD1306/nano_gfx.su ./Modules/Devices/SSD1306/sova.cyclo ./Modules/Devices/SSD1306/sova.d ./Modules/Devices/SSD1306/sova.o ./Modules/Devices/SSD1306/sova.su ./Modules/Devices/SSD1306/sprite_pool.cyclo ./Modules/Devices/SSD1306/sprite_pool.d ./Modules/Devices/SSD1306/sprite_pool.o ./Modules/Devices/SSD1306/sprite_pool.su ./Modules/Devices/SSD1306/ssd1306_16bit.cyclo ./Modules/Devices/SSD1306/ssd1306_16bit.d ./Modules/Devices/SSD1306/ssd1306_16bit.o ./Modules/Devices/SSD1306/ssd1306_16bit.su ./Modules/Devices/SSD1306/ssd1306_1bit.cyclo ./Modules/Devices/SSD1306/ssd1306_1bit.d ./Modules/Devices/SSD1306/ssd1306_1bit.o ./Modules/Devices/SSD1306/ssd1306_1bit.su ./Modules/Devices/SSD1306/ssd1306_8bit.cyclo ./Modules/Devices/SSD1306/ssd1306_8bit.d ./Modules/Devices/SSD1306/ssd1306_8bit.o ./Modules/Devices/SSD1306/ssd1306_8bit.su ./Modules/Devices/SSD1306/ssd1306_console.cyclo ./Modules/Devices/SSD1306/ssd1306_console.d ./Modules/Devices/SSD1306/ssd1306_console.o ./Modules/Devices/SSD1306/ssd1306_console.su ./Modules/Devices/SSD1306/ssd1306_fonts.cyclo ./Modules/Devices/SSD1306/ssd1306_fonts.d ./Modules/Devices/SSD1306/ssd1306_fonts.o ./Modules/Devices/SSD1306/ssd1306_fonts.su ./Modules/Devices/SSD1306/ssd1306_generic.cyclo ./Modules/Devices/SSD1306/ssd1306_generic.d ./Modules/Devices/SSD1306/ssd1306_generic.o ./Modules/Devices/SSD1306/ssd1306_generic.su ./Modules/Devices/SSD1306/ssd1306_menu.cyclo ./Modules/Devices/SSD1306/ssd1306_menu.d ./Modules/Devices/SSD1306/ssd1306_menu.o ./Modules/Devices/SSD1306/ssd1306_menu.su

.PHONY: clean-Modules-2f-Devices-2f-SSD1306

