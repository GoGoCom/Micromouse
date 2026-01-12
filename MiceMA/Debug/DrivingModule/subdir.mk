################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DrivingModule/CDriveEncoders.cpp \
../DrivingModule/CDriveMotors.cpp \
../DrivingModule/CDriveProfile.cpp \
../DrivingModule/CDriveReports.cpp \
../DrivingModule/CDriveSensors.cpp 

C_SRCS += \
../DrivingModule/customMath.c 

C_DEPS += \
./DrivingModule/customMath.d 

OBJS += \
./DrivingModule/CDriveEncoders.o \
./DrivingModule/CDriveMotors.o \
./DrivingModule/CDriveProfile.o \
./DrivingModule/CDriveReports.o \
./DrivingModule/CDriveSensors.o \
./DrivingModule/customMath.o 

CPP_DEPS += \
./DrivingModule/CDriveEncoders.d \
./DrivingModule/CDriveMotors.d \
./DrivingModule/CDriveProfile.d \
./DrivingModule/CDriveReports.d \
./DrivingModule/CDriveSensors.d 


# Each subdirectory must supply rules for building sources it contributes
DrivingModule/%.o DrivingModule/%.su DrivingModule/%.cyclo: ../DrivingModule/%.cpp DrivingModule/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers/SSD1306" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers/EEPROM" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Module" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/DrivingModule" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
DrivingModule/%.o DrivingModule/%.su DrivingModule/%.cyclo: ../DrivingModule/%.c DrivingModule/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers/SSD1306" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Drivers/EEPROM" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/Module" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceE/DrivingModule" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-DrivingModule

clean-DrivingModule:
	-$(RM) ./DrivingModule/CDriveEncoders.cyclo ./DrivingModule/CDriveEncoders.d ./DrivingModule/CDriveEncoders.o ./DrivingModule/CDriveEncoders.su ./DrivingModule/CDriveMotors.cyclo ./DrivingModule/CDriveMotors.d ./DrivingModule/CDriveMotors.o ./DrivingModule/CDriveMotors.su ./DrivingModule/CDriveProfile.cyclo ./DrivingModule/CDriveProfile.d ./DrivingModule/CDriveProfile.o ./DrivingModule/CDriveProfile.su ./DrivingModule/CDriveReports.cyclo ./DrivingModule/CDriveReports.d ./DrivingModule/CDriveReports.o ./DrivingModule/CDriveReports.su ./DrivingModule/CDriveSensors.cyclo ./DrivingModule/CDriveSensors.d ./DrivingModule/CDriveSensors.o ./DrivingModule/CDriveSensors.su ./DrivingModule/customMath.cyclo ./DrivingModule/customMath.d ./DrivingModule/customMath.o ./DrivingModule/customMath.su

.PHONY: clean-DrivingModule

