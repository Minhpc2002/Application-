#ifndef __MKL46_ADC_H__
#define __MKL46_ADC_H__

#include "MKL46Z4.h"
#include "core_cm0plus.h"
#include "system_MKL46Z4.h"

typedef void (*ADC_CallbackType)();

typedef enum{
	ADC_ADICLK_BUSCLK 				= 0u,
	ADC_ADICLK_BUSCLK_DIV_2 		= 1u,
	ADC_ADICLK_ALTCLK 				= 2u,
	ADC_ADICLK_ADACK 				= 3u,
}ADC_ClockSourceType;

typedef enum{
	ADC_ADIV_DIV_1			= 0u,
	ADC_ADIV_DIV_2			= 1u,
	ADC_ADIV_DIV_4			= 2u,
	ADC_ADIV_DIV_8			= 3u,
}ADC_ClockDevideType;

typedef enum{
	ADC_VREF_DEFAULT 		= 0u,
	ADC_VREF_ALTPIN			= 1u,
}ADC_VrefSourceType;

typedef enum{
	ADC_TRIG_SOFTWARE		= 0u,
	ADC_TRIG_HAREWARE		= 1u,
}ADC_TriggerType;

typedef enum{
	ADC_ONE_CONV		= 0u,
	ADC_CONTINOUUS_CONV	= 1u,
}ADC_ContinuousType;

typedef enum{
	ADC_MODE_SINGLEEND 		= 0u,
	ADC_MODE_DIFFERENTIAL	= 1u,
}ADC_SignalModeType;

typedef enum{
	ADC_RES_8_9_BIT			= 0u,
	ADC_RES_12_13_BIT		= 1u,
	ADC_RES_10_11_BIT		= 2u,
	ADC_RES_16_16_BIT		= 3u,
}ADC_ResolutionType;

typedef enum{
	ADC_CHANNEL_A	= 0u,
	ADC_CHANNEL_B	= 1u,
}ADC_ChannelType;

typedef enum {
	ADC_INPUT_ADC0 = 0u,
	ADC_INPUT_ADC1 = 1u,
	ADC_INPUT_ADC2 = 2u,
	ADC_INPUT_ADC3 = 3u,
	ADC_INPUT_ADC4 = 4u,
	ADC_INPUT_ADC5 = 5u,
	ADC_INPUT_ADC6 = 6u,
	ADC_INPUT_ADC7 = 7u,
	ADC_INPUT_ADC8 = 8u,
	ADC_INPUT_ADC9 = 9u,
	ADC_INPUT_ADC10 = 10u,
	ADC_INPUT_ADC11 = 11u,
	ADC_INPUT_ADC12 = 12u,
	ADC_INPUT_ADC13 = 13u,
	ADC_INPUT_ADC14 = 14u,
	ADC_INPUT_ADC15 = 15u,
	ADC_INPUT_ADC16 = 16u,
	ADC_INPUT_ADC17 = 17u,
	ADC_INPUT_ADC18 = 18u,
	ADC_INPUT_ADC19 = 19u,
	ADC_INPUT_ADC20 = 20u,
	ADC_INPUT_ADC21 = 21u,
	ADC_INPUT_ADC22 = 22u,
	ADC_INPUT_ADC23 = 23u,
	ADC_INPUT_INTEMP = 26u,
	ADC_INPUT_BANDGAP = 27u,
	ADC_INPUT_VREFSH = 29u,
	ADC_INPUT_VREFSL = 30u,
	ADC_INPUT_DISABLE = 31u,

}ADC_InputChannelType;

typedef enum{
	ADC_INTERRUPT_DISABLE = 0u,
	ADC_INTERRUPT_ENABLE = 1u,
}ADC_InterruptType;

typedef struct{
	ADC_ChannelType channel ;
	ADC_ClockSourceType clock ;
	ADC_ClockDevideType devide ;
	ADC_TriggerType trig ;
	ADC_VrefSourceType vref ;
	ADC_ContinuousType cont ;
	ADC_SignalModeType diff ;
	ADC_ResolutionType res ;
	ADC_InterruptType interrupt;
	ADC_CallbackType callback;
}ADC_ConfigType;

void ADC_Init(ADC_Type* ADC, const ADC_ConfigType* config) ;
void ADC_StartConv(ADC_Type* ADC, ADC_ChannelType channel, uint8_t input) ;
int16_t readADC(ADC_Type* ADC, ADC_ChannelType channel, uint8_t input) ;
void ADC_SetCallBack(ADC_CallbackType callback);

#endif

