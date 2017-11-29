################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/rclab/workspace/cdc/cdc.c \
/home/rclab/workspace/cdc/usb_descriptors.c \
/home/rclab/workspace/cdc/usb_device.c 

OBJS += \
./cdc/cdc.o \
./cdc/usb_descriptors.o \
./cdc/usb_device.o 

C_DEPS += \
./cdc/cdc.d \
./cdc/usb_descriptors.d \
./cdc/usb_device.d 


# Each subdirectory must supply rules for building sources it contributes
cdc/cdc.o: /home/rclab/workspace/cdc/cdc.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	mips-sde-elf-gcc -D__PIC32MX__ -I../../p32mx250f128/ -I../../cdc/ -O0 -g3 -Wall -c -fmessage-length=0 -march=m4k -EL -msoft-float -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

cdc/usb_descriptors.o: /home/rclab/workspace/cdc/usb_descriptors.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	mips-sde-elf-gcc -D__PIC32MX__ -I../../p32mx250f128/ -I../../cdc/ -O0 -g3 -Wall -c -fmessage-length=0 -march=m4k -EL -msoft-float -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

cdc/usb_device.o: /home/rclab/workspace/cdc/usb_device.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	mips-sde-elf-gcc -D__PIC32MX__ -I../../p32mx250f128/ -I../../cdc/ -O0 -g3 -Wall -c -fmessage-length=0 -march=m4k -EL -msoft-float -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


