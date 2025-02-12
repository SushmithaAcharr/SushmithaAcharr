################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/rm_freertos_port/port.c 

SREC += \
Pump_Sada.srec 

C_DEPS += \
./ra/fsp/src/rm_freertos_port/port.d 

OBJS += \
./ra/fsp/src/rm_freertos_port/port.o 

MAP += \
Pump_Sada.map 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/rm_freertos_port/%.o: ../ra/fsp/src/rm_freertos_port/%.c
	$(file > $@.in,-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-strict-aliasing -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM4 -D_RA_ORDINAL=1 -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/src" -I"." -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/inc" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/inc/api" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/inc/instances" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/src/rm_freertos_port" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/aws/FreeRTOS/FreeRTOS/Source/include" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_gen" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_cfg/fsp_cfg/bsp" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_cfg/fsp_cfg" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_cfg/aws" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/src/r_usb_basic/src/driver/inc" -std=c99 -Wno-stringop-overflow -Wno-format-truncation --param=min-pagesize=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

