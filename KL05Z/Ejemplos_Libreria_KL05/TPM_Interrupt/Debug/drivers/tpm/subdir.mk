################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/Ejemplos_Libreria_KL05/drivers/tpm/tpm.c 

OBJS += \
./drivers/tpm/tpm.o 

C_DEPS += \
./drivers/tpm/tpm.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/tpm/tpm.o: F:/Ejemplos_Libreria_KL05/drivers/tpm/tpm.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -I"F:\Ejemplos_Libreria_KL05\drivers\adc" -I"F:\Ejemplos_Libreria_KL05\drivers\clk" -I"F:\Ejemplos_Libreria_KL05\drivers\dac" -I"F:\Ejemplos_Libreria_KL05\drivers\gpio" -I"F:\Ejemplos_Libreria_KL05\drivers\lptmr" -I"F:\Ejemplos_Libreria_KL05\drivers\tpm" -I"F:\Ejemplos_Libreria_KL05\drivers\uart" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


