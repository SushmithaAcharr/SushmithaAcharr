################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra_gen/common_data.c \
../ra_gen/config_thread0.c \
../ra_gen/display_thread.c \
../ra_gen/fan_control_thread.c \
../ra_gen/hal_data.c \
../ra_gen/main.c \
../ra_gen/modbus_thread.c \
../ra_gen/pin_data.c \
../ra_gen/ui_task.c \
../ra_gen/vector_data.c 

SREC += \
Pump_Sada.srec 

C_DEPS += \
./ra_gen/common_data.d \
./ra_gen/config_thread0.d \
./ra_gen/display_thread.d \
./ra_gen/fan_control_thread.d \
./ra_gen/hal_data.d \
./ra_gen/main.d \
./ra_gen/modbus_thread.d \
./ra_gen/pin_data.d \
./ra_gen/ui_task.d \
./ra_gen/vector_data.d 

OBJS += \
./ra_gen/common_data.o \
./ra_gen/config_thread0.o \
./ra_gen/display_thread.o \
./ra_gen/fan_control_thread.o \
./ra_gen/hal_data.o \
./ra_gen/main.o \
./ra_gen/modbus_thread.o \
./ra_gen/pin_data.o \
./ra_gen/ui_task.o \
./ra_gen/vector_data.o 

MAP += \
Pump_Sada.map 


# Each subdirectory must supply rules for building sources it contributes
ra_gen/%.o: ../ra_gen/%.c
	$(file > $@.in,-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-strict-aliasing -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM4 -D_RA_ORDINAL=1 -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/src" -I"." -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/inc" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/inc/api" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/inc/instances" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/src/rm_freertos_port" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/aws/FreeRTOS/FreeRTOS/Source/include" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_gen" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_cfg/fsp_cfg/bsp" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_cfg/fsp_cfg" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_cfg/aws" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/src/r_usb_basic/src/driver/inc" -std=c99 -Wno-stringop-overflow -Wno-format-truncation --param=min-pagesize=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

