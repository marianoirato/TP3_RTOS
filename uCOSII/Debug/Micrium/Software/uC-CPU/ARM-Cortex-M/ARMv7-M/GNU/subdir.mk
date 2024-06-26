################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/GNU/cpu_a.s 

OBJS += \
./Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/GNU/cpu_a.o 

S_DEPS += \
./Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/GNU/cpu_a.d 


# Each subdirectory must supply rules for building sources it contributes
Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/GNU/%.o: ../Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/GNU/%.s Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/GNU/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Micrium-2f-Software-2f-uC-2d-CPU-2f-ARM-2d-Cortex-2d-M-2f-ARMv7-2d-M-2f-GNU

clean-Micrium-2f-Software-2f-uC-2d-CPU-2f-ARM-2d-Cortex-2d-M-2f-ARMv7-2d-M-2f-GNU:
	-$(RM) ./Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/GNU/cpu_a.d ./Micrium/Software/uC-CPU/ARM-Cortex-M/ARMv7-M/GNU/cpu_a.o

.PHONY: clean-Micrium-2f-Software-2f-uC-2d-CPU-2f-ARM-2d-Cortex-2d-M-2f-ARMv7-2d-M-2f-GNU

