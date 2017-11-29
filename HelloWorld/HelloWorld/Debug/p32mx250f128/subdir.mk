################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
/home/rclab/workspace/p32mx250f128/processor.o 

S_UPPER_SRCS += \
/home/rclab/workspace/p32mx250f128/crt0.S 

OBJS += \
./p32mx250f128/crt0.o 


# Each subdirectory must supply rules for building sources it contributes
p32mx250f128/crt0.o: /home/rclab/workspace/p32mx250f128/crt0.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	mips-sde-elf-g++ -c -march=m4k -EL -I../../p32mx250f128/ -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


