################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Ejemplos_Libreria_KL05/drivers/clk/clk.c 

OBJS += \
./drivers/clk/clk.o 

C_DEPS += \
./drivers/clk/clk.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/clk/clk.o: D:/Ejemplos_Libreria_KL05/drivers/clk/clk.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -I"D:\Ejemplos_Libreria_KL05\drivers\gpio" -I"D:\Ejemplos_Libreria_KL05\drivers\clk" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

