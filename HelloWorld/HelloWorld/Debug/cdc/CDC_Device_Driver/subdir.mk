################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/rclab/workspace/cdc/CDC_Device_Driver/usb_function_cdc.c 

OBJS += \
./cdc/CDC_Device_Driver/usb_function_cdc.o 

C_DEPS += \
./cdc/CDC_Device_Driver/usb_function_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
cdc/CDC_Device_Driver/usb_function_cdc.o: /home/rclab/workspace/cdc/CDC_Device_Driver/usb_function_cdc.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	mips-sde-elf-gcc -D__PIC32MX__ -I../../p32mx250f128/ -I../../cdc/ -O0 -g3 -Wall -c -fmessage-length=0 -march=m4k -EL -msoft-float -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


