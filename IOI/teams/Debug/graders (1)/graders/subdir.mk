################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../graders\ (1)/graders/grader.cpp \
../graders\ (1)/graders/teams.cpp 

C_SRCS += \
../graders\ (1)/graders/grader.c \
../graders\ (1)/graders/teams.c 

OBJS += \
./graders\ (1)/graders/grader.o \
./graders\ (1)/graders/teams.o 

CPP_DEPS += \
./graders\ (1)/graders/grader.d \
./graders\ (1)/graders/teams.d 

C_DEPS += \
./graders\ (1)/graders/grader.d \
./graders\ (1)/graders/teams.d 


# Each subdirectory must supply rules for building sources it contributes
graders\ (1)/graders/grader.o: ../graders\ (1)/graders/grader.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"graders (1)/graders/grader.d" -MT"graders\ (1)/graders/grader.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

graders\ (1)/graders/grader.o: ../graders\ (1)/graders/grader.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"graders (1)/graders/grader.d" -MT"graders\ (1)/graders/grader.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

graders\ (1)/graders/teams.o: ../graders\ (1)/graders/teams.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"graders (1)/graders/teams.d" -MT"graders\ (1)/graders/teams.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

graders\ (1)/graders/teams.o: ../graders\ (1)/graders/teams.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"graders (1)/graders/teams.d" -MT"graders\ (1)/graders/teams.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


