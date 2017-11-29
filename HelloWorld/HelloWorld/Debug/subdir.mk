################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardwareInit.c 

CPP_SRCS += \
../main.cpp 

S_UPPER_SRCS += \
../isr.S 

OBJS += \
./hardwareInit.o \
./isr.o \
./main.o 

C_DEPS += \
./hardwareInit.d 

CPP_DEPS += \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	mips-sde-elf-gcc -D__PIC32MX__ -I../../p32mx250f128/ -I../../cdc/ -O0 -g3 -Wall -c -fmessage-length=0 -march=m4k -EL -msoft-float -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	mips-sde-elf-g++ -c -march=m4k -EL -I../../p32mx250f128/ -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	mips-sde-elf-g++ -I../../p32mx250f128 -O0 -g3 -Wall -c -fmessage-length=0 -march=m4k -EL -fno-exceptions -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


