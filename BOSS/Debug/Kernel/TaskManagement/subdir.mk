################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Kernel/TaskManagement/TaskManager.cpp 

CPP_DEPS += \
./Kernel/TaskManagement/TaskManager.pp 

OBJS += \
./Kernel/TaskManagement/TaskManager.obj 

OBJS__QTD += \
".\Kernel\TaskManagement\TaskManager.obj" 

CPP_DEPS__QTD += \
".\Kernel\TaskManagement\TaskManager.pp" 

CPP_SRCS_QUOTED += \
"../Kernel/TaskManagement/TaskManager.cpp" 


# Each subdirectory must supply rules for building sources it contributes
Kernel/TaskManagement/TaskManager.obj: ../Kernel/TaskManagement/TaskManager.cpp $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/tms470/bin/cl470" -mv7A8 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/tms470/include" --diag_warning=225 -me --enum_type=packed --code_state=32 --preproc_with_compile --preproc_dependency="Kernel/TaskManagement/TaskManager.pp" --obj_directory="Kernel/TaskManagement" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


