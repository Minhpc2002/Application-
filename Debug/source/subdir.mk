################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/App_at_sector_50.c \
../source/adc.c \
../source/gpio.c \
../source/mtb.c \
../source/port.c \
../source/printf.c \
../source/semihost_hardfault.c \
../source/uart.c 

C_DEPS += \
./source/App_at_sector_50.d \
./source/adc.d \
./source/gpio.d \
./source/mtb.d \
./source/port.d \
./source/printf.d \
./source/semihost_hardfault.d \
./source/uart.d 

OBJS += \
./source/App_at_sector_50.o \
./source/adc.o \
./source/gpio.o \
./source/mtb.o \
./source/port.o \
./source/printf.o \
./source/semihost_hardfault.o \
./source/uart.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL46Z256VLL4 -DCPU_MKL46Z256VLL4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=1 -DPRINTF_FLOAT_ENABLE=0 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"H:\C_Embeded_FPT\Mooc\Firmware\Appication\App_50\source" -I"H:\C_Embeded_FPT\Mooc\Firmware\Appication\App_50" -I"H:\C_Embeded_FPT\Mooc\Firmware\Appication\App_50\CMSIS" -I"H:\C_Embeded_FPT\Mooc\Firmware\Appication\App_50\startup" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/App_at_sector_50.d ./source/App_at_sector_50.o ./source/adc.d ./source/adc.o ./source/gpio.d ./source/gpio.o ./source/mtb.d ./source/mtb.o ./source/port.d ./source/port.o ./source/printf.d ./source/printf.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/uart.d ./source/uart.o

.PHONY: clean-source

