################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/developer/Clones/boggart/PAL/Lib/Instantiator.cpp 

OBJS += \
./Lib/Instantiator.o 

CPP_DEPS += \
./Lib/Instantiator.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/Instantiator.o: /home/developer/Clones/boggart/PAL/Lib/Instantiator.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


