################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Src/usbd_hid.c 

OBJS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/HID/Src/usbd_hid.o 

C_DEPS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/HID/Src/usbd_hid.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Device_Library/Class/HID/Src/usbd_hid.o: ../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Src/usbd_hid.c
	arm-none-eabi-gcc -gdwarf-4 "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -I"C:/Users/rvt20/STM32CubeIDE/workspace_1.4.0/SR_Mycha/Drivers/BSP" -I"C:/Users/rvt20/STM32CubeIDE/workspace_1.4.0/SR_Mycha/Drivers/BSP/STM32L476G-Discovery" -I"C:/Users/rvt20/STM32CubeIDE/workspace_1.4.0/SR_Mycha/Drivers/BSP/Components/l3gd20" -I"C:/Users/rvt20/STM32CubeIDE/workspace_1.4.0/SR_Mycha/Drivers/BSP/Components/lsm303c" -I"C:/Users/rvt20/STM32CubeIDE/workspace_1.4.0/SR_Mycha/Drivers/BSP/Components/Common" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USB_Device_Library/Class/HID/Src/usbd_hid.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

