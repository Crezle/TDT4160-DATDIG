################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../o3.c 

OBJS += \
./o3.o 

C_DEPS += \
./o3.d 


# Each subdirectory must supply rules for building sources it contributes
o3.o: ../o3.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"o3.d" -MT"o3.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


