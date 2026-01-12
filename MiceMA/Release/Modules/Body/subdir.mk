################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Modules/Body/CBody.cpp \
../Modules/Body/CDriveEncoders.cpp \
../Modules/Body/CDriveMotors.cpp \
../Modules/Body/CDriveProfile.cpp \
../Modules/Body/CDriveReports.cpp \
../Modules/Body/CDriveSensors.cpp \
../Modules/Body/OneButton.cpp 

OBJS += \
./Modules/Body/CBody.o \
./Modules/Body/CDriveEncoders.o \
./Modules/Body/CDriveMotors.o \
./Modules/Body/CDriveProfile.o \
./Modules/Body/CDriveReports.o \
./Modules/Body/CDriveSensors.o \
./Modules/Body/OneButton.o 

CPP_DEPS += \
./Modules/Body/CBody.d \
./Modules/Body/CDriveEncoders.d \
./Modules/Body/CDriveMotors.d \
./Modules/Body/CDriveProfile.d \
./Modules/Body/CDriveReports.d \
./Modules/Body/CDriveSensors.d \
./Modules/Body/OneButton.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/Body/%.o Modules/Body/%.su Modules/Body/%.cyclo: ../Modules/Body/%.cpp Modules/Body/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Drivers" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Body" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Brain" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Devices/EEPROM" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Devices/SSD1306" -I"C:/Users/apex6/Desktop/NewMiceRobots/MiceMA/Modules/Mices" -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Modules-2f-Body

clean-Modules-2f-Body:
	-$(RM) ./Modules/Body/CBody.cyclo ./Modules/Body/CBody.d ./Modules/Body/CBody.o ./Modules/Body/CBody.su ./Modules/Body/CDriveEncoders.cyclo ./Modules/Body/CDriveEncoders.d ./Modules/Body/CDriveEncoders.o ./Modules/Body/CDriveEncoders.su ./Modules/Body/CDriveMotors.cyclo ./Modules/Body/CDriveMotors.d ./Modules/Body/CDriveMotors.o ./Modules/Body/CDriveMotors.su ./Modules/Body/CDriveProfile.cyclo ./Modules/Body/CDriveProfile.d ./Modules/Body/CDriveProfile.o ./Modules/Body/CDriveProfile.su ./Modules/Body/CDriveReports.cyclo ./Modules/Body/CDriveReports.d ./Modules/Body/CDriveReports.o ./Modules/Body/CDriveReports.su ./Modules/Body/CDriveSensors.cyclo ./Modules/Body/CDriveSensors.d ./Modules/Body/CDriveSensors.o ./Modules/Body/CDriveSensors.su ./Modules/Body/OneButton.cyclo ./Modules/Body/OneButton.d ./Modules/Body/OneButton.o ./Modules/Body/OneButton.su

.PHONY: clean-Modules-2f-Body

