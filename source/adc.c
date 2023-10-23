#include <adc.h>
#define NULL ((void*)0)

static ADC_CallbackType s_gADCCallbackFunction = NULL;

__STATIC_INLINE void ADC_SetCLK(ADC_Type* ADC, ADC_ClockSourceType clock){
	//Select clock source for ADC
		ADC->CFG1 &= ~ADC_CFG1_ADICLK_MASK ;
		ADC->CFG1 |= ADC_CFG1_ADICLK((uint32_t)clock) ; // bus clock
}

__STATIC_INLINE void ADC_SelVref(ADC_Type* ADC, ADC_VrefSourceType vref){
	// Select voltage reference
		ADC->SC2 &= ~ADC_SC2_REFSEL_MASK ; // VREFSH and VREFSL
		ADC->SC2 |= ADC_SC2_REFSEL((uint32_t)vref) ;
}
__STATIC_INLINE void ADC_SelTrig(ADC_Type* ADC, ADC_TriggerType trig){
	// Select trigger
		ADC->SC2 &= ~ADC_SC2_ADTRG_MASK ;
		ADC->SC2 |= ADC_SC2_ADTRG((uint32_t)trig) ;
}
__STATIC_INLINE void ADC_SetConvType(ADC_Type* ADC, ADC_ContinuousType mode){
	//Continuous Conversion Enable
		ADC->SC3 &= ~ADC_SC3_ADCO_MASK ;
		ADC->SC3 |= ADC_SC3_ADCO((uint32_t)mode) ;
}
__STATIC_INLINE void ADC_SelInputType(ADC_Type* ADC, ADC_ChannelType channel, ADC_SignalModeType diff){
	//single-ended or differential
		ADC->SC1[(uint32_t)channel] &= ~ADC_SC1_DIFF_MASK ;
		ADC->SC1[(uint32_t)channel] |= ADC_SC1_DIFF((uint32_t) diff) ;
}
__STATIC_INLINE void ADC_SetResolution(ADC_Type* ADC, ADC_ResolutionType res){
	// Config resolution
		ADC->CFG1 &= ~ADC_CFG1_MODE_MASK ;
		ADC->CFG1 |= ADC_CFG1_MODE((uint32_t)res);
}
void ADC_SetCallBack(ADC_CallbackType callback){
	s_gADCCallbackFunction = callback ;
}
__STATIC_INLINE uint8_t ADC_CheckCOCO(ADC_Type* ADC, ADC_ChannelType channel){
	return (ADC->SC1[(uint32_t)channel] & ADC_SC1_COCO_MASK) == 0?0:1 ;
}
__STATIC_INLINE void ADC_SetInterrupt(ADC_Type* ADC, ADC_ChannelType channel, ADC_InterruptType interrupt){
	ADC->SC1[(uint32_t)channel] &= ~ADC_SC1_AIEN_MASK ;
	ADC->SC1[(uint32_t)channel] |= ADC_SC1_AIEN((uint32_t)interrupt) ;
}
__STATIC_INLINE void ADC_DisableModule(ADC_Type* ADC, ADC_ChannelType channel){
	ADC->SC1[(uint32_t)channel] |= ADC_SC1_ADCH_MASK ;
}
void ADC_Init(ADC_Type* ADC, const ADC_ConfigType* config) {
	ADC_SetCLK(ADC, config->clock) ;
	ADC_SelVref(ADC, config->vref) ;
	ADC_SelTrig(ADC, config->trig) ;
	ADC_SetConvType(ADC, config->cont) ;
	ADC_SelInputType(ADC, config->channel, config->diff) ;
	ADC_SetResolution(ADC, config->res) ;
	ADC_SetInterrupt(ADC, config->channel, config->interrupt) ;
	ADC_SetCallBack(config->callback) ;
	if(ADC_INTERRUPT_ENABLE == config->interrupt){
		NVIC_EnableIRQ(ADC0_IRQn) ;
	}
}

void ADC_StartConv(ADC_Type* ADC, ADC_ChannelType channel, uint8_t input){
	// Select ADC channel
	ADC->CFG2 &= ~ADC_CFG2_MUXSEL_MASK ; // select channel 2
	// Start conversion
	ADC->SC1[channel] = ((ADC->SC1[channel]) & (~ADC_SC1_ADCH_MASK)) | ADC_SC1_ADCH(input) ;
}

int16_t readADC(ADC_Type* ADC, ADC_ChannelType channel, uint8_t input){
	while(ADC_CheckCOCO(ADC, channel) == 0) ;
	return ADC0->R[channel] ;
}

void ADC0_IRQHandler(){
	if(s_gADCCallbackFunction != NULL){
		s_gADCCallbackFunction() ;
	}
	else{
//		ADC0->R[ADC_CHANNEL_A] ; // Clear Interupt flag
	}
}

