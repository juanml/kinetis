################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Ejemplos_Libreria_KL05/drivers/tpm/tpm.c 

OBJS += \
./drivers/tpm/tpm.o 

C_DEPS += \
./drivers/tpm/tpm.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/tpm/tpm.o: C:/Ejemplos_Libreria_KL05/drivers/tpm/tpm.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -I"C:\Ejemplos_Libreria_KL05\drivers\ds18b20" -I"C:\Ejemplos_Libreria_KL05\drivers\clk" -I"C:\Ejemplos_Libreria_KL05\drivers\gpio" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


