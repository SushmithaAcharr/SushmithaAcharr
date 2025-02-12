################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/aws/FreeRTOS/FreeRTOS/Source/event_groups.c \
../ra/aws/FreeRTOS/FreeRTOS/Source/list.c \
../ra/aws/FreeRTOS/FreeRTOS/Source/queue.c \
../ra/aws/FreeRTOS/FreeRTOS/Source/stream_buffer.c \
../ra/aws/FreeRTOS/FreeRTOS/Source/tasks.c \
../ra/aws/FreeRTOS/FreeRTOS/Source/timers.c 

SREC += \
Pump_Sada.srec 

C_DEPS += \
./ra/aws/FreeRTOS/FreeRTOS/Source/event_groups.d \
./ra/aws/FreeRTOS/FreeRTOS/Source/list.d \
./ra/aws/FreeRTOS/FreeRTOS/Source/queue.d \
./ra/aws/FreeRTOS/FreeRTOS/Source/stream_buffer.d \
./ra/aws/FreeRTOS/FreeRTOS/Source/tasks.d \
./ra/aws/FreeRTOS/FreeRTOS/Source/timers.d 

OBJS += \
./ra/aws/FreeRTOS/FreeRTOS/Source/event_groups.o \
./ra/aws/FreeRTOS/FreeRTOS/Source/list.o \
./ra/aws/FreeRTOS/FreeRTOS/Source/queue.o \
./ra/aws/FreeRTOS/FreeRTOS/Source/stream_buffer.o \
./ra/aws/FreeRTOS/FreeRTOS/Source/tasks.o \
./ra/aws/FreeRTOS/FreeRTOS/Source/timers.o 

MAP += \
Pump_Sada.map 


# Each subdirectory must supply rules for building sources it contributes
ra/aws/FreeRTOS/FreeRTOS/Source/%.o: ../ra/aws/FreeRTOS/FreeRTOS/Source/%.c
	$(file > $@.in,-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-strict-aliasing -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM4 -D_RA_ORDINAL=1 -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/src" -I"." -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/inc" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/inc/api" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/inc/instances" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/src/rm_freertos_port" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/aws/FreeRTOS/FreeRTOS/Source/include" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_gen" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_cfg/fsp_cfg/bsp" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_cfg/fsp_cfg" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_cfg/aws" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/src/r_usb_basic/src/driver/inc" -std=c99 -Wno-stringop-overflow -Wno-format-truncation -w --param=min-pagesize=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

