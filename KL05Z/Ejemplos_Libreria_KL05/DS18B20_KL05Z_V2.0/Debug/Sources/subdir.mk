################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/1-wire.c \
../Sources/WAIT1.c \
../Sources/ds18b20.c \
../Sources/main.c 

OBJS += \
./Sources/1-wire.o \
./Sources/WAIT1.o \
./Sources/ds18b20.o \
./Sources/main.o 

C_DEPS += \
./Sources/1-wire.d \
./Sources/WAIT1.d \
./Sources/ds18b20.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -I"D:\Ejemplos_Libreria_KL05\drivers\gpio" -I"D:\Ejemplos_Libreria_KL05\drivers\clk" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


