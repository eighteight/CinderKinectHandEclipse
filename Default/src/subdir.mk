################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/KinectHand.cpp 

OBJS += \
./src/KinectHand.o 

CPP_DEPS += \
./src/KinectHand.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/Users/boba/repos/Cinder/boost -I/Users/boba/repos/Cinder/blocks/Cinder-OpenCV/include -I/Users/boba/repos/Cinder/include -I"/Users/boba/Documents/workspace/CinderKinectHandEclipse/includes/OpenNI" -I"/Users/boba/Documents/workspace/CinderKinectHandEclipse/includes" -O0 -g -Wall -c -fmessage-length=0 -arch i386 -x objective-c++ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


