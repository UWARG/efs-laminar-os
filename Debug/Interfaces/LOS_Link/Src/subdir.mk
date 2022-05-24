################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Interfaces/LOS_Link/Src/RSSI.cpp 

OBJS += \
./Interfaces/LOS_Link/Src/RSSI.o 

CPP_DEPS += \
./Interfaces/LOS_Link/Src/RSSI.d 


# Each subdirectory must supply rules for building sources it contributes
Interfaces/LOS_Link/Src/%.o Interfaces/LOS_Link/Src/%.su: ../Interfaces/LOS_Link/Src/%.cpp Interfaces/LOS_Link/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I"/Users/anthony/Documents/Code/ZP_Proto_Port/LaminarOS/Interfaces" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Interfaces-2f-LOS_Link-2f-Src

clean-Interfaces-2f-LOS_Link-2f-Src:
	-$(RM) ./Interfaces/LOS_Link/Src/RSSI.d ./Interfaces/LOS_Link/Src/RSSI.o ./Interfaces/LOS_Link/Src/RSSI.su

.PHONY: clean-Interfaces-2f-LOS_Link-2f-Src

