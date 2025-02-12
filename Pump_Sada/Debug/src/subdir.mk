################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AlarmManager.cpp \
../src/AspDevice.cpp \
../src/ConfigManager.cpp \
../src/FanControl.cpp \
../src/FanSchedular.cpp \
../src/FansManager.cpp \
../src/FaultCodeDatabase.cpp \
../src/FlashStorage.cpp \
../src/ModbusRTUSlave.cpp \
../src/TempContol.cpp \
../src/TempHysterisis.cpp \
../src/UI.cpp \
../src/config_thread0_entry.cpp \
../src/display_thread_entry.cpp \
../src/fan_control_thread_entry.cpp \
../src/hal_entry.cpp \
../src/modbus_thread_entry.cpp \
../src/ui_task_entry.cpp 

C_SRCS += \
../src/MAX31865.c \
../src/r_usb_pcdc_descriptor.c 

SREC += \
Pump_Sada.srec 

C_DEPS += \
./src/MAX31865.d \
./src/r_usb_pcdc_descriptor.d 

OBJS += \
./src/AlarmManager.o \
./src/AspDevice.o \
./src/ConfigManager.o \
./src/FanControl.o \
./src/FanSchedular.o \
./src/FansManager.o \
./src/FaultCodeDatabase.o \
./src/FlashStorage.o \
./src/MAX31865.o \
./src/ModbusRTUSlave.o \
./src/TempContol.o \
./src/TempHysterisis.o \
./src/UI.o \
./src/config_thread0_entry.o \
./src/display_thread_entry.o \
./src/fan_control_thread_entry.o \
./src/hal_entry.o \
./src/modbus_thread_entry.o \
./src/r_usb_pcdc_descriptor.o \
./src/ui_task_entry.o 

MAP += \
Pump_Sada.map 

CPP_DEPS += \
./src/AlarmManager.d \
./src/AspDevice.d \
./src/ConfigManager.d \
./src/FanControl.d \
./src/FanSchedular.d \
./src/FansManager.d \
./src/FaultCodeDatabase.d \
./src/FlashStorage.d \
./src/ModbusRTUSlave.d \
./src/TempContol.d \
./src/TempHysterisis.d \
./src/UI.d \
./src/config_thread0_entry.d \
./src/display_thread_entry.d \
./src/fan_control_thread_entry.d \
./src/hal_entry.d \
./src/modbus_thread_entry.d \
./src/ui_task_entry.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	$(file > $@.in,-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-strict-aliasing -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM4 -D_RA_ORDINAL=1 -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/src" -I"." -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/inc" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/inc/api" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/inc/instances" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/src/rm_freertos_port" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/aws/FreeRTOS/FreeRTOS/Source/include" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_gen" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_cfg/fsp_cfg/bsp" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_cfg/fsp_cfg" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_cfg/aws" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/src/r_usb_basic/src/driver/inc" -std=c++11 -fabi-version=0 -Wno-stringop-overflow -Wno-format-truncation --param=min-pagesize=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c++ "$<")
	@echo Building file: $< && arm-none-eabi-g++ @"$@.in"
src/%.o: ../src/%.c
	$(file > $@.in,-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-strict-aliasing -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM4 -D_RA_ORDINAL=1 -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/src" -I"." -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/inc" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/inc/api" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/inc/instances" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/src/rm_freertos_port" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/aws/FreeRTOS/FreeRTOS/Source/include" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_gen" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_cfg/fsp_cfg/bsp" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_cfg/fsp_cfg" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_cfg/aws" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/src/r_usb_basic/src/driver/inc" -std=c99 -Wno-stringop-overflow -Wno-format-truncation --param=min-pagesize=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

