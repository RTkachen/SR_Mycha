################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32L476G-Discovery/stm32l476g_discovery.c \
../Drivers/BSP/STM32L476G-Discovery/stm32l476g_discovery_compass.c \
../Drivers/BSP/STM32L476G-Discovery/stm32l476g_discovery_gyroscope.c 

OBJS += \
./Drivers/BSP/STM32L476G-Discovery/stm32l476g_discovery.o \
./Drivers/BSP/STM32L476G-Discovery/stm32l476g_discovery_compass.o \
./Drivers/BSP/STM32L476G-Discovery/stm32l476g_discovery_gyroscope.o 

C_DEPS += \
./Drivers/BSP/STM32L476G-Discovery/stm32l476g_discovery.d \
./Drivers/BSP/STM32L476G-Discovery/stm32l476g_discovery_compass.d \
./Drivers/BSP/STM32L476G-Discovery/stm32l476g_discovery_gyroscope.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32L476G-Discovery/stm32l476g_discovery.o: ../Drivers/BSP/STM32L476G-Discovery/stm32l476g_discovery.c
	arm-none-eabi-gcc -gdwarf-4 "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -I"C:/Users/rvt20/STM32CubeIDE/workspace_1.4.0/SR_Mycha/Drivers/BSP" -I"C:/Users/rvt20/STM32CubeIDE/workspace_1.4.0/SR_Mycha/Drivers/BSP/STM32L476G-Discovery" -I"C:/Users/rvt20/STM32CubeIDE/workspace_1.4.0/SR_Mycha/Drivers/BSP/Components/l3gd20" -I"C:/Users/rvt20/STM32CubeIDE/workspace_1.4.0/SR_Mycha/Drivers/BSP/Components/lsm303c" -I"C:/Users/rvt20/STM32CubeIDE/workspace_1.4.0/SR_Mycha/Drivers/BSP/Components/Common" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM32L476G-Discovery/stm32l476g_discovery.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32L476G-Discovery/stm32l476g_discovery_compass.o: ../Drivers/BSP/STM32L476G-Discovery/stm32l476g_discovery_compass.c
	arm-none-eabi-gcc -gdwarf-4 "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -I"C:/Users/rvt20/STM32CubeIDE/workspace_1.4.0/SR_Mycha/Drivers/BSP" -I"C:/Users/rvt20/STM32CubeIDE/workspace_1.4.0/SR_Mycha/Drivers/BSP/STM32L476G-Discovery" -I"C:/Users/rvt20/STM32CubeIDE/workspace_1.4.0/SR_Mycha/Drivers/BSP/Components/l3gd20" -I"C:/Users/rvt20/STM32CubeIDE/workspace_1.4.0/SR_Mycha/Drivers/BSP/Components/lsm303c" -I"C:/Users/rvt20/STM32CubeIDE/workspace_1.4.0/SR_Mycha/Drivers/BSP/Components/Common" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM32L476G-Discovery/stm32l476g_discovery_compass.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32L476G-Discovery/stm32l476g_discovery_gyroscope.o: ../Drivers/BSP/STM32L476G-Discovery/stm32l476g_discovery_gyroscope.c
	arm-none-eabi-gcc -gdwarf-4 "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -I"C:/Users/rvt20/STM32CubeIDE/workspace_1.4.0/SR_Mycha/Drivers/BSP" -I"C:/Users/rvt20/STM32CubeIDE/workspace_1.4.0/SR_Mycha/Drivers/BSP/STM32L476G-Discovery" -I"C:/Users/rvt20/STM32CubeIDE/workspace_1.4.0/SR_Mycha/Drivers/BSP/Components/l3gd20" -I"C:/Users/rvt20/STM32CubeIDE/workspace_1.4.0/SR_Mycha/Drivers/BSP/Components/lsm303c" -I"C:/Users/rvt20/STM32CubeIDE/workspace_1.4.0/SR_Mycha/Drivers/BSP/Components/Common" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM32L476G-Discovery/stm32l476g_discovery_gyroscope.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

