################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gpt/Gpt.c 

OBJS += \
./Gpt/Gpt.o 

C_DEPS += \
./Gpt/Gpt.d 


# Each subdirectory must supply rules for building sources it contributes
Gpt/%.o: ../Gpt/%.c Gpt/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra -g -DNDEBUG -DSTM32F401xE -DHSE_VALUE=8000000 -I"../include" -I"C:\Users\hp\Desktop\test_project\Gpt" -I"C:\Users\hp\Desktop\test_project\Gpio" -I"C:\Users\hp\Desktop\test_project\Lib" -I"C:\Users\hp\Desktop\test_project\Rcc" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


