################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/adc.c \
../Sources/clk.c \
../Sources/dac.c \
../Sources/gpio.c \
../Sources/lptmr.c \
../Sources/main.c \
../Sources/tpm.c 

OBJS += \
./Sources/adc.o \
./Sources/clk.o \
./Sources/dac.o \
./Sources/gpio.o \
./Sources/lptmr.o \
./Sources/main.o \
./Sources/tpm.o 

C_DEPS += \
./Sources/adc.d \
./Sources/clk.d \
./Sources/dac.d \
./Sources/gpio.d \
./Sources/lptmr.d \
./Sources/main.d \
./Sources/tpm.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


