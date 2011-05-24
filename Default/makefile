################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: CinderKinectHandEclipse

# Tool invocations
CinderKinectHandEclipse: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MacOS X C++ Linker'
	g++ -L"/Users/gusev/Documents/workspace/CinderKinectHandEclipse/libs" -L"/Users/gusev/repos/Nite-1.3.1.5/bin" -L"/Users/gusev/repos/Nite-1.3.1.5/Features_1_3_1/Bin" -L"/Users/gusev/repos/Nite-1.3.1.5/Hands_1_3_1/Bin" -arch i386 -framework Cocoa -framework OpenGL -framework Carbon -framework CoreVideo -framework QTKit -framework QuickTime -framework Accelerate -framework AudioToolbox -framework AudioUnit -framework CoreAudio -Xlinker /Users/gusev/repos/Cinder/lib/libcinder_d.a /Users/gusev/repos/Cinder/blocks/Cinder-OpenCV/lib/macosx/libcv.a /Users/gusev/repos/Cinder/blocks/Cinder-OpenCV/lib/macosx/libcxcore.a -o "CinderKinectHandEclipse" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) CinderKinectHandEclipse
	-@echo ' '

post-build:
	-mkdir -p CinderKinectHandEclipse.app/Contents/MacOS ; mv CinderKinectHandEclipse CinderKinectHandEclipse.app/Contents/MacOS/ ; cp -rf ../Resources CinderKinectHandEclipse.app/Contents/Resources ; cp -rf ../Resources/Info.plist CinderKinectHandEclipse.app/Contents/Info.plist
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
