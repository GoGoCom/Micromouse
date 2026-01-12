################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Modules/Mices/AdultMouse.cpp \
../Modules/Mices/BabyMouse.cpp \
../Modules/Mices/CMice.cpp \
../Modules/Mices/OldMouse.cpp \
../Modules/Mices/YoungAdultMouse.cpp \
../Modules/Mices/YoungMouse.cpp 

OBJS += \
./Modules/Mices/AdultMouse.o \
./Modules/Mices/BabyMouse.o \
./Modules/Mices/CMice.o \
./Modules/Mices/OldMouse.o \
./Modules/Mices/YoungAdultMouse.o \
./Modules/Mices/YoungMouse.o 

CPP_DEPS += \
./Modules/Mices/AdultMouse.d \
./Modules/Mices/BabyMouse.d \
./Modules/Mices/CMice.d \
./Modules/Mices/OldMouse.d \
./Modules/Mices/YoungAdultMouse.d \
./Modules/Mices/YoungMouse.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/Mices/%.o Modules/Mices/%.su Modules/Mices/%.cyclo: ../Modules/Mices/%.cpp Modules/Mices/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Drivers" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Body" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Brain" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Devices/EEPROM" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Devices/SSD1306" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Mices" -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Modules-2f-Mices

clean-Modules-2f-Mices:
	-$(RM) ./Modules/Mices/AdultMouse.cyclo ./Modules/Mices/AdultMouse.d ./Modules/Mices/AdultMouse.o ./Modules/Mices/AdultMouse.su ./Modules/Mices/BabyMouse.cyclo ./Modules/Mices/BabyMouse.d ./Modules/Mices/BabyMouse.o ./Modules/Mices/BabyMouse.su ./Modules/Mices/CMice.cyclo ./Modules/Mices/CMice.d ./Modules/Mices/CMice.o ./Modules/Mices/CMice.su ./Modules/Mices/OldMouse.cyclo ./Modules/Mices/OldMouse.d ./Modules/Mices/OldMouse.o ./Modules/Mices/OldMouse.su ./Modules/Mices/YoungAdultMouse.cyclo ./Modules/Mices/YoungAdultMouse.d ./Modules/Mices/YoungAdultMouse.o ./Modules/Mices/YoungAdultMouse.su ./Modules/Mices/YoungMouse.cyclo ./Modules/Mices/YoungMouse.d ./Modules/Mices/YoungMouse.o ./Modules/Mices/YoungMouse.su

.PHONY: clean-Modules-2f-Mices

