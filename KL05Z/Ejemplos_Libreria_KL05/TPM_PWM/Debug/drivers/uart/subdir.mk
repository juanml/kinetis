################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/Ejemplos_Libreria_KL05/drivers/uart/uart.c 

OBJS += \
./drivers/uart/uart.o 

C_DEPS += \
./drivers/uart/uart.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/uart/uart.o: F:/Ejemplos_Libreria_KL05/drivers/uart/uart.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -I"F:\Ejemplos_Libreria_KL05\drivers\adc" -I"F:\Ejemplos_Libreria_KL05\drivers\clk" -I"F:\Ejemplos_Libreria_KL05\drivers\dac" -I"F:\Ejemplos_Libreria_KL05\drivers\gpio" -I"F:\Ejemplos_Libreria_KL05\drivers\tpm" -I"F:\Ejemplos_Libreria_KL05\drivers\uart" -I"F:\Ejemplos_Libreria_KL05\drivers\lptmr" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


