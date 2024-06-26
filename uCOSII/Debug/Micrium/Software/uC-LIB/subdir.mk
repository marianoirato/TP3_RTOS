################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Micrium/Software/uC-LIB/lib_ascii.c \
../Micrium/Software/uC-LIB/lib_math.c \
../Micrium/Software/uC-LIB/lib_mem.c \
../Micrium/Software/uC-LIB/lib_str.c 

OBJS += \
./Micrium/Software/uC-LIB/lib_ascii.o \
./Micrium/Software/uC-LIB/lib_math.o \
./Micrium/Software/uC-LIB/lib_mem.o \
./Micrium/Software/uC-LIB/lib_str.o 

C_DEPS += \
./Micrium/Software/uC-LIB/lib_ascii.d \
./Micrium/Software/uC-LIB/lib_math.d \
./Micrium/Software/uC-LIB/lib_mem.d \
./Micrium/Software/uC-LIB/lib_str.d 


# Each subdirectory must supply rules for building sources it contributes
Micrium/Software/uC-LIB/%.o Micrium/Software/uC-LIB/%.su Micrium/Software/uC-LIB/%.cyclo: ../Micrium/Software/uC-LIB/%.c Micrium/Software/uC-LIB/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../USB_DEVICE/Target -I../Micrium/Template/OS2 -I../Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/GNU -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Micrium/Template -I../Micrium/Software/uCOS-II/Source -I../Micrium/Software/uC-LIB -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Micrium/Software/uC-CPU -I../Micrium/Software/uCOS-II/Ports/ARM-Cortex-M/ARMv7-M/GNU -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Micrium-2f-Software-2f-uC-2d-LIB

clean-Micrium-2f-Software-2f-uC-2d-LIB:
	-$(RM) ./Micrium/Software/uC-LIB/lib_ascii.cyclo ./Micrium/Software/uC-LIB/lib_ascii.d ./Micrium/Software/uC-LIB/lib_ascii.o ./Micrium/Software/uC-LIB/lib_ascii.su ./Micrium/Software/uC-LIB/lib_math.cyclo ./Micrium/Software/uC-LIB/lib_math.d ./Micrium/Software/uC-LIB/lib_math.o ./Micrium/Software/uC-LIB/lib_math.su ./Micrium/Software/uC-LIB/lib_mem.cyclo ./Micrium/Software/uC-LIB/lib_mem.d ./Micrium/Software/uC-LIB/lib_mem.o ./Micrium/Software/uC-LIB/lib_mem.su ./Micrium/Software/uC-LIB/lib_str.cyclo ./Micrium/Software/uC-LIB/lib_str.d ./Micrium/Software/uC-LIB/lib_str.o ./Micrium/Software/uC-LIB/lib_str.su

.PHONY: clean-Micrium-2f-Software-2f-uC-2d-LIB

