################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/UiPAges/AboutPage.cpp \
../src/UiPAges/AlertPage.cpp \
../src/UiPAges/BuzzerSettingPage.cpp \
../src/UiPAges/CalibrationPage.cpp \
../src/UiPAges/ChangePwdPage.cpp \
../src/UiPAges/DashBoard.cpp \
../src/UiPAges/DateTimeSettingPage.cpp \
../src/UiPAges/ExtFireSignalPage.cpp \
../src/UiPAges/FactoryResetPage.cpp \
../src/UiPAges/FaultHistPage.cpp \
../src/UiPAges/GsmSettingsPage.cpp \
../src/UiPAges/HeatWarningPage.cpp \
../src/UiPAges/MiscSettingsPage.cpp \
../src/UiPAges/PasswordPage.cpp \
../src/UiPAges/Rs485SettingsPage.cpp \
../src/UiPAges/SettingsPage.cpp \
../src/UiPAges/SplashPage.cpp \
../src/UiPAges/TempSensorFailedPage.cpp \
../src/UiPAges/TempSettingsPage.cpp \
../src/UiPAges/UnitFailurePage.cpp \
../src/UiPAges/UnitSettingPage.cpp \
../src/UiPAges/WrongPwdPage.cpp 

SREC += \
Pump_Sada.srec 

OBJS += \
./src/UiPAges/AboutPage.o \
./src/UiPAges/AlertPage.o \
./src/UiPAges/BuzzerSettingPage.o \
./src/UiPAges/CalibrationPage.o \
./src/UiPAges/ChangePwdPage.o \
./src/UiPAges/DashBoard.o \
./src/UiPAges/DateTimeSettingPage.o \
./src/UiPAges/ExtFireSignalPage.o \
./src/UiPAges/FactoryResetPage.o \
./src/UiPAges/FaultHistPage.o \
./src/UiPAges/GsmSettingsPage.o \
./src/UiPAges/HeatWarningPage.o \
./src/UiPAges/MiscSettingsPage.o \
./src/UiPAges/PasswordPage.o \
./src/UiPAges/Rs485SettingsPage.o \
./src/UiPAges/SettingsPage.o \
./src/UiPAges/SplashPage.o \
./src/UiPAges/TempSensorFailedPage.o \
./src/UiPAges/TempSettingsPage.o \
./src/UiPAges/UnitFailurePage.o \
./src/UiPAges/UnitSettingPage.o \
./src/UiPAges/WrongPwdPage.o 

MAP += \
Pump_Sada.map 

CPP_DEPS += \
./src/UiPAges/AboutPage.d \
./src/UiPAges/AlertPage.d \
./src/UiPAges/BuzzerSettingPage.d \
./src/UiPAges/CalibrationPage.d \
./src/UiPAges/ChangePwdPage.d \
./src/UiPAges/DashBoard.d \
./src/UiPAges/DateTimeSettingPage.d \
./src/UiPAges/ExtFireSignalPage.d \
./src/UiPAges/FactoryResetPage.d \
./src/UiPAges/FaultHistPage.d \
./src/UiPAges/GsmSettingsPage.d \
./src/UiPAges/HeatWarningPage.d \
./src/UiPAges/MiscSettingsPage.d \
./src/UiPAges/PasswordPage.d \
./src/UiPAges/Rs485SettingsPage.d \
./src/UiPAges/SettingsPage.d \
./src/UiPAges/SplashPage.d \
./src/UiPAges/TempSensorFailedPage.d \
./src/UiPAges/TempSettingsPage.d \
./src/UiPAges/UnitFailurePage.d \
./src/UiPAges/UnitSettingPage.d \
./src/UiPAges/WrongPwdPage.d 


# Each subdirectory must supply rules for building sources it contributes
src/UiPAges/%.o: ../src/UiPAges/%.cpp
	$(file > $@.in,-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-strict-aliasing -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM4 -D_RA_ORDINAL=1 -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/src" -I"." -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/inc" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/inc/api" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/inc/instances" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/src/rm_freertos_port" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/aws/FreeRTOS/FreeRTOS/Source/include" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_gen" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_cfg/fsp_cfg/bsp" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_cfg/fsp_cfg" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra_cfg/aws" -I"C:/Users/3250u_x1/e2_studio/workspace/Pump_Sada/ra/fsp/src/r_usb_basic/src/driver/inc" -std=c++11 -fabi-version=0 -Wno-stringop-overflow -Wno-format-truncation --param=min-pagesize=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c++ "$<")
	@echo Building file: $< && arm-none-eabi-g++ @"$@.in"

