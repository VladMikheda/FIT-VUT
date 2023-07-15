################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/addons.c \
../Sources/init.c \
../Sources/main.c \
../Sources/times.c \
../Sources/uart.c 

OBJS += \
./Sources/addons.o \
./Sources/init.o \
./Sources/main.o \
./Sources/times.o \
./Sources/uart.o 

C_DEPS += \
./Sources/addons.d \
./Sources/init.d \
./Sources/main.d \
./Sources/times.d \
./Sources/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


