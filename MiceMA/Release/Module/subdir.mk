################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Module/AdultMouse.cpp \
../Module/BabyMouse.cpp \
../Module/Buffers.cpp \
../Module/CBody.cpp \
../Module/CBrain.cpp \
../Module/CMice.cpp \
../Module/Cerebellum.cpp \
../Module/Cerebrum.cpp \
../Module/Floodfill.cpp \
../Module/NewMouse.cpp \
../Module/Nodes.cpp \
../Module/OldMouse.cpp \
../Module/OneButton.cpp \
../Module/Simulation.cpp \
../Module/YoungMouse.cpp 

OBJS += \
./Module/AdultMouse.o \
./Module/BabyMouse.o \
./Module/Buffers.o \
./Module/CBody.o \
./Module/CBrain.o \
./Module/CMice.o \
./Module/Cerebellum.o \
./Module/Cerebrum.o \
./Module/Floodfill.o \
./Module/NewMouse.o \
./Module/Nodes.o \
./Module/OldMouse.o \
./Module/OneButton.o \
./Module/Simulation.o \
./Module/YoungMouse.o 

CPP_DEPS += \
./Module/AdultMouse.d \
./Module/BabyMouse.d \
./Module/Buffers.d \
./Module/CBody.d \
./Module/CBrain.d \
./Module/CMice.d \
./Module/Cerebellum.d \
./Module/Cerebrum.d \
./Module/Floodfill.d \
./Module/NewMouse.d \
./Module/Nodes.d \
./Module/OldMouse.d \
./Module/OneButton.d \
./Module/Simulation.d \
./Module/YoungMouse.d 


# Each subdirectory must supply rules for building sources it contributes
Module/%.o Module/%.su Module/%.cyclo: ../Module/%.cpp Module/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers/SSD1306" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers/EEPROM" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Module" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/DrivingModule" -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Module

clean-Module:
	-$(RM) ./Module/AdultMouse.cyclo ./Module/AdultMouse.d ./Module/AdultMouse.o ./Module/AdultMouse.su ./Module/BabyMouse.cyclo ./Module/BabyMouse.d ./Module/BabyMouse.o ./Module/BabyMouse.su ./Module/Buffers.cyclo ./Module/Buffers.d ./Module/Buffers.o ./Module/Buffers.su ./Module/CBody.cyclo ./Module/CBody.d ./Module/CBody.o ./Module/CBody.su ./Module/CBrain.cyclo ./Module/CBrain.d ./Module/CBrain.o ./Module/CBrain.su ./Module/CMice.cyclo ./Module/CMice.d ./Module/CMice.o ./Module/CMice.su ./Module/Cerebellum.cyclo ./Module/Cerebellum.d ./Module/Cerebellum.o ./Module/Cerebellum.su ./Module/Cerebrum.cyclo ./Module/Cerebrum.d ./Module/Cerebrum.o ./Module/Cerebrum.su ./Module/Floodfill.cyclo ./Module/Floodfill.d ./Module/Floodfill.o ./Module/Floodfill.su ./Module/NewMouse.cyclo ./Module/NewMouse.d ./Module/NewMouse.o ./Module/NewMouse.su ./Module/Nodes.cyclo ./Module/Nodes.d ./Module/Nodes.o ./Module/Nodes.su ./Module/OldMouse.cyclo ./Module/OldMouse.d ./Module/OldMouse.o ./Module/OldMouse.su ./Module/OneButton.cyclo ./Module/OneButton.d ./Module/OneButton.o ./Module/OneButton.su ./Module/Simulation.cyclo ./Module/Simulation.d ./Module/Simulation.o ./Module/Simulation.su ./Module/YoungMouse.cyclo ./Module/YoungMouse.d ./Module/YoungMouse.o ./Module/YoungMouse.su

.PHONY: clean-Module

