################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/cpu_c.c 

OBJS += \
./Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/cpu_c.o 

C_DEPS += \
./Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/cpu_c.d 


# Each subdirectory must supply rules for building sources it contributes
Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/%.o Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/%.su Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/%.cyclo: ../Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/%.c Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../USB_DEVICE/Target -I../Micrium/Template/OS2 -I../Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/GNU -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Micrium/Template -I../Micrium/Software/uCOS-II/Source -I../Micrium/Software/uC-LIB -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Micrium/Software/uC-CPU -I../Micrium/Software/uCOS-II/Ports/ARM-Cortex-M/ARMv7-M/GNU -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Micrium-2f-Software-2f-uC-2d-CPU-2f-ARM-2d-Cortex-2d-M-2f-ARMv7-2d-M

clean-Micrium-2f-Software-2f-uC-2d-CPU-2f-ARM-2d-Cortex-2d-M-2f-ARMv7-2d-M:
	-$(RM) ./Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/cpu_c.cyclo ./Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/cpu_c.d ./Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/cpu_c.o ./Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/cpu_c.su

.PHONY: clean-Micrium-2f-Software-2f-uC-2d-CPU-2f-ARM-2d-Cortex-2d-M-2f-ARMv7-2d-M

