################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Micrium/Software/uCOS-II/Source/os_core.c \
../Micrium/Software/uCOS-II/Source/os_flag.c \
../Micrium/Software/uCOS-II/Source/os_mbox.c \
../Micrium/Software/uCOS-II/Source/os_mem.c \
../Micrium/Software/uCOS-II/Source/os_mutex.c \
../Micrium/Software/uCOS-II/Source/os_q.c \
../Micrium/Software/uCOS-II/Source/os_sem.c \
../Micrium/Software/uCOS-II/Source/os_task.c \
../Micrium/Software/uCOS-II/Source/os_time.c \
../Micrium/Software/uCOS-II/Source/os_tmr.c 

OBJS += \
./Micrium/Software/uCOS-II/Source/os_core.o \
./Micrium/Software/uCOS-II/Source/os_flag.o \
./Micrium/Software/uCOS-II/Source/os_mbox.o \
./Micrium/Software/uCOS-II/Source/os_mem.o \
./Micrium/Software/uCOS-II/Source/os_mutex.o \
./Micrium/Software/uCOS-II/Source/os_q.o \
./Micrium/Software/uCOS-II/Source/os_sem.o \
./Micrium/Software/uCOS-II/Source/os_task.o \
./Micrium/Software/uCOS-II/Source/os_time.o \
./Micrium/Software/uCOS-II/Source/os_tmr.o 

C_DEPS += \
./Micrium/Software/uCOS-II/Source/os_core.d \
./Micrium/Software/uCOS-II/Source/os_flag.d \
./Micrium/Software/uCOS-II/Source/os_mbox.d \
./Micrium/Software/uCOS-II/Source/os_mem.d \
./Micrium/Software/uCOS-II/Source/os_mutex.d \
./Micrium/Software/uCOS-II/Source/os_q.d \
./Micrium/Software/uCOS-II/Source/os_sem.d \
./Micrium/Software/uCOS-II/Source/os_task.d \
./Micrium/Software/uCOS-II/Source/os_time.d \
./Micrium/Software/uCOS-II/Source/os_tmr.d 


# Each subdirectory must supply rules for building sources it contributes
Micrium/Software/uCOS-II/Source/%.o Micrium/Software/uCOS-II/Source/%.su Micrium/Software/uCOS-II/Source/%.cyclo: ../Micrium/Software/uCOS-II/Source/%.c Micrium/Software/uCOS-II/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../USB_DEVICE/Target -I../Micrium/Template/OS2 -I../Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/GNU -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Micrium/Template -I../Micrium/Software/uCOS-II/Source -I../Micrium/Software/uC-LIB -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../USB_DEVICE/App -I../Micrium/Software/uC-CPU -I../Micrium/Software/uCOS-II/Ports/ARM-Cortex-M/ARMv7-M/GNU -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Micrium-2f-Software-2f-uCOS-2d-II-2f-Source

clean-Micrium-2f-Software-2f-uCOS-2d-II-2f-Source:
	-$(RM) ./Micrium/Software/uCOS-II/Source/os_core.cyclo ./Micrium/Software/uCOS-II/Source/os_core.d ./Micrium/Software/uCOS-II/Source/os_core.o ./Micrium/Software/uCOS-II/Source/os_core.su ./Micrium/Software/uCOS-II/Source/os_flag.cyclo ./Micrium/Software/uCOS-II/Source/os_flag.d ./Micrium/Software/uCOS-II/Source/os_flag.o ./Micrium/Software/uCOS-II/Source/os_flag.su ./Micrium/Software/uCOS-II/Source/os_mbox.cyclo ./Micrium/Software/uCOS-II/Source/os_mbox.d ./Micrium/Software/uCOS-II/Source/os_mbox.o ./Micrium/Software/uCOS-II/Source/os_mbox.su ./Micrium/Software/uCOS-II/Source/os_mem.cyclo ./Micrium/Software/uCOS-II/Source/os_mem.d ./Micrium/Software/uCOS-II/Source/os_mem.o ./Micrium/Software/uCOS-II/Source/os_mem.su ./Micrium/Software/uCOS-II/Source/os_mutex.cyclo ./Micrium/Software/uCOS-II/Source/os_mutex.d ./Micrium/Software/uCOS-II/Source/os_mutex.o ./Micrium/Software/uCOS-II/Source/os_mutex.su ./Micrium/Software/uCOS-II/Source/os_q.cyclo ./Micrium/Software/uCOS-II/Source/os_q.d ./Micrium/Software/uCOS-II/Source/os_q.o ./Micrium/Software/uCOS-II/Source/os_q.su ./Micrium/Software/uCOS-II/Source/os_sem.cyclo ./Micrium/Software/uCOS-II/Source/os_sem.d ./Micrium/Software/uCOS-II/Source/os_sem.o ./Micrium/Software/uCOS-II/Source/os_sem.su ./Micrium/Software/uCOS-II/Source/os_task.cyclo ./Micrium/Software/uCOS-II/Source/os_task.d ./Micrium/Software/uCOS-II/Source/os_task.o ./Micrium/Software/uCOS-II/Source/os_task.su ./Micrium/Software/uCOS-II/Source/os_time.cyclo ./Micrium/Software/uCOS-II/Source/os_time.d ./Micrium/Software/uCOS-II/Source/os_time.o ./Micrium/Software/uCOS-II/Source/os_time.su ./Micrium/Software/uCOS-II/Source/os_tmr.cyclo ./Micrium/Software/uCOS-II/Source/os_tmr.d ./Micrium/Software/uCOS-II/Source/os_tmr.o ./Micrium/Software/uCOS-II/Source/os_tmr.su

.PHONY: clean-Micrium-2f-Software-2f-uCOS-2d-II-2f-Source

