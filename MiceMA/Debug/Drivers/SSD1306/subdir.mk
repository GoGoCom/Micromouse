################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drivers/SSD1306/nano_gfx.cpp \
../Drivers/SSD1306/sova.cpp \
../Drivers/SSD1306/sprite_pool.cpp \
../Drivers/SSD1306/ssd1306_console.cpp 

C_SRCS += \
../Drivers/SSD1306/ssd1306_16bit.c \
../Drivers/SSD1306/ssd1306_1bit.c \
../Drivers/SSD1306/ssd1306_8bit.c \
../Drivers/SSD1306/ssd1306_fonts.c \
../Drivers/SSD1306/ssd1306_generic.c \
../Drivers/SSD1306/ssd1306_menu.c 

C_DEPS += \
./Drivers/SSD1306/ssd1306_16bit.d \
./Drivers/SSD1306/ssd1306_1bit.d \
./Drivers/SSD1306/ssd1306_8bit.d \
./Drivers/SSD1306/ssd1306_fonts.d \
./Drivers/SSD1306/ssd1306_generic.d \
./Drivers/SSD1306/ssd1306_menu.d 

OBJS += \
./Drivers/SSD1306/nano_gfx.o \
./Drivers/SSD1306/sova.o \
./Drivers/SSD1306/sprite_pool.o \
./Drivers/SSD1306/ssd1306_16bit.o \
./Drivers/SSD1306/ssd1306_1bit.o \
./Drivers/SSD1306/ssd1306_8bit.o \
./Drivers/SSD1306/ssd1306_console.o \
./Drivers/SSD1306/ssd1306_fonts.o \
./Drivers/SSD1306/ssd1306_generic.o \
./Drivers/SSD1306/ssd1306_menu.o 

CPP_DEPS += \
./Drivers/SSD1306/nano_gfx.d \
./Drivers/SSD1306/sova.d \
./Drivers/SSD1306/sprite_pool.d \
./Drivers/SSD1306/ssd1306_console.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SSD1306/%.o Drivers/SSD1306/%.su Drivers/SSD1306/%.cyclo: ../Drivers/SSD1306/%.cpp Drivers/SSD1306/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers/SSD1306" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers/EEPROM" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Module" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/DrivingModule" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/SSD1306/%.o Drivers/SSD1306/%.su Drivers/SSD1306/%.cyclo: ../Drivers/SSD1306/%.c Drivers/SSD1306/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers/SSD1306" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers/EEPROM" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Module" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/DrivingModule" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-SSD1306

clean-Drivers-2f-SSD1306:
	-$(RM) ./Drivers/SSD1306/nano_gfx.cyclo ./Drivers/SSD1306/nano_gfx.d ./Drivers/SSD1306/nano_gfx.o ./Drivers/SSD1306/nano_gfx.su ./Drivers/SSD1306/sova.cyclo ./Drivers/SSD1306/sova.d ./Drivers/SSD1306/sova.o ./Drivers/SSD1306/sova.su ./Drivers/SSD1306/sprite_pool.cyclo ./Drivers/SSD1306/sprite_pool.d ./Drivers/SSD1306/sprite_pool.o ./Drivers/SSD1306/sprite_pool.su ./Drivers/SSD1306/ssd1306_16bit.cyclo ./Drivers/SSD1306/ssd1306_16bit.d ./Drivers/SSD1306/ssd1306_16bit.o ./Drivers/SSD1306/ssd1306_16bit.su ./Drivers/SSD1306/ssd1306_1bit.cyclo ./Drivers/SSD1306/ssd1306_1bit.d ./Drivers/SSD1306/ssd1306_1bit.o ./Drivers/SSD1306/ssd1306_1bit.su ./Drivers/SSD1306/ssd1306_8bit.cyclo ./Drivers/SSD1306/ssd1306_8bit.d ./Drivers/SSD1306/ssd1306_8bit.o ./Drivers/SSD1306/ssd1306_8bit.su ./Drivers/SSD1306/ssd1306_console.cyclo ./Drivers/SSD1306/ssd1306_console.d ./Drivers/SSD1306/ssd1306_console.o ./Drivers/SSD1306/ssd1306_console.su ./Drivers/SSD1306/ssd1306_fonts.cyclo ./Drivers/SSD1306/ssd1306_fonts.d ./Drivers/SSD1306/ssd1306_fonts.o ./Drivers/SSD1306/ssd1306_fonts.su ./Drivers/SSD1306/ssd1306_generic.cyclo ./Drivers/SSD1306/ssd1306_generic.d ./Drivers/SSD1306/ssd1306_generic.o ./Drivers/SSD1306/ssd1306_generic.su ./Drivers/SSD1306/ssd1306_menu.cyclo ./Drivers/SSD1306/ssd1306_menu.d ./Drivers/SSD1306/ssd1306_menu.o ./Drivers/SSD1306/ssd1306_menu.su

.PHONY: clean-Drivers-2f-SSD1306

