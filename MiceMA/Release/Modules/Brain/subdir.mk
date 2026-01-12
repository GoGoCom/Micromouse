################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Modules/Brain/Buffers.cpp \
../Modules/Brain/CBrain.cpp \
../Modules/Brain/Cerebellum.cpp \
../Modules/Brain/Cerebrum.cpp \
../Modules/Brain/Floodfill.cpp \
../Modules/Brain/Nodes.cpp \
../Modules/Brain/Simulation.cpp 

OBJS += \
./Modules/Brain/Buffers.o \
./Modules/Brain/CBrain.o \
./Modules/Brain/Cerebellum.o \
./Modules/Brain/Cerebrum.o \
./Modules/Brain/Floodfill.o \
./Modules/Brain/Nodes.o \
./Modules/Brain/Simulation.o 

CPP_DEPS += \
./Modules/Brain/Buffers.d \
./Modules/Brain/CBrain.d \
./Modules/Brain/Cerebellum.d \
./Modules/Brain/Cerebrum.d \
./Modules/Brain/Floodfill.d \
./Modules/Brain/Nodes.d \
./Modules/Brain/Simulation.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/Brain/%.o Modules/Brain/%.su Modules/Brain/%.cyclo: ../Modules/Brain/%.cpp Modules/Brain/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Drivers" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Body" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Brain" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Devices/EEPROM" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Devices/SSD1306" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Mices" -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Modules-2f-Brain

clean-Modules-2f-Brain:
	-$(RM) ./Modules/Brain/Buffers.cyclo ./Modules/Brain/Buffers.d ./Modules/Brain/Buffers.o ./Modules/Brain/Buffers.su ./Modules/Brain/CBrain.cyclo ./Modules/Brain/CBrain.d ./Modules/Brain/CBrain.o ./Modules/Brain/CBrain.su ./Modules/Brain/Cerebellum.cyclo ./Modules/Brain/Cerebellum.d ./Modules/Brain/Cerebellum.o ./Modules/Brain/Cerebellum.su ./Modules/Brain/Cerebrum.cyclo ./Modules/Brain/Cerebrum.d ./Modules/Brain/Cerebrum.o ./Modules/Brain/Cerebrum.su ./Modules/Brain/Floodfill.cyclo ./Modules/Brain/Floodfill.d ./Modules/Brain/Floodfill.o ./Modules/Brain/Floodfill.su ./Modules/Brain/Nodes.cyclo ./Modules/Brain/Nodes.d ./Modules/Brain/Nodes.o ./Modules/Brain/Nodes.su ./Modules/Brain/Simulation.cyclo ./Modules/Brain/Simulation.d ./Modules/Brain/Simulation.o ./Modules/Brain/Simulation.su

.PHONY: clean-Modules-2f-Brain

