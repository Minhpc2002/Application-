
#include "MKL46Z4.h"
#include "core_cm0plus.h"
#include "system_MKL46Z4.h"

#include "port.h"
#include "gpio.h"
#include "uart.h"
#include "adc.h"
#include <stdio.h>


#define TIMER_RElOAD_VALUE  (999999u)	// 1 milisecond period
//#define TIMER_RElOAD_VALUE  (1999999u)	// 2 milisecond period
#define MAX_LEN_HISTORY	(10u)

#define LED_Pin 		(5u)
#define LED_PORT		(PORTD)
#define LED_GPIO		(GPIOD)

uint8_t cmd_key = 0x55 ;
const float TempSensorSlope = 1.62 ;
const float TempSensorVolt25 = 716 ;
float Temp_History[MAX_LEN_HISTORY] ;

void clock_init() ;
void system_init() ;
void systick_init() ;




void main()
{
	char buffer[50] ;
	system_init() ;

	sprintf(buffer, "\nSend 0x%x to get data\n", cmd_key) ;
	uart_sendString(buffer) ;

	while(1)
	{
		if(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)
		{
			ADC_StartConv(ADC0, ADC_CHANNEL_A, ADC_INPUT_INTEMP) ;
			int16_t ADC_result ;
			ADC_result =  readADC(ADC0, ADC_CHANNEL_A, ADC_INPUT_INTEMP) ;
			float Voltage ;
			Voltage = (float)ADC_result/ 0xfffe * 3300 ;

			for(int i= 0; i < MAX_LEN_HISTORY - 1; i ++)
			{
				Temp_History[i] = Temp_History[i+1] ;
			}
			Temp_History[MAX_LEN_HISTORY - 1] = (25 - (Voltage - TempSensorVolt25 )/ TempSensorSlope) ;
			GPIO_TogglePin(LED_GPIO, LED_Pin) ;
		}

		if(uart_available())
		{

			uint8_t byte ;
			byte = (uint8_t)uart_getByte() ;
			if(cmd_key == byte)
			{
				for(int i= 0; i < MAX_LEN_HISTORY; i ++)
				{
					sprintf(buffer, "  %.2f", Temp_History[i]);
					uart_sendString(buffer) ;
				}
				uart_sendByte('\n') ;
			}
		}
	}



}

void system_init()
{
	/* Clock init to get 1Mhz from internal clock*/
		clock_init() ;

	/* LED Init*/
		PORT_PinConfigType led_port_config = {
				.ALTMode = PORT_ALT_GPIO,
				.pull = PORT_NOPULL,
		};
		PORT_InitPin(LED_PORT, LED_Pin, &led_port_config) ;

		GPIO_PinConfigType led_gpio_config = {
				.direction = GPIO_OUTPUT,
				.state = GPIO_PIN_RESET,
		};
		GPIO_InitPin(LED_GPIO, LED_Pin, &led_gpio_config) ;


	/* UART Initial */
		PORT_PinConfigType uart_port_config = {
				.ALTMode = PORT_AFT_2,
				.pull = PORT_PULLUP,
		};
		PORT_InitPin(PORTA, 1, &uart_port_config) ;
		PORT_InitPin(PORTA, 2, &uart_port_config) ;

		uart_init() ;

	/* ADC Initial	 */
		const ADC_ConfigType ADC_config = {
				.channel = ADC_CHANNEL_A,
				.clock = ADC_ADICLK_BUSCLK,
				.devide = ADC_ADIV_DIV_1,
				.trig = ADC_TRIG_SOFTWARE ,
				.vref = ADC_VREF_DEFAULT,
				.cont = ADC_ONE_CONV,
				.diff = ADC_MODE_SINGLEEND,
				.res = ADC_RES_16_16_BIT,
				.interrupt = ADC_INTERRUPT_DISABLE ,
		};
		ADC_Init(ADC0, &ADC_config) ;

	/* Timer initial*/
		systick_init();
}

void clock_init()
{
	// Clock init to have 1 Mhz core clock
	// Select internal clock
	MCG->C1 &= ~MCG_C1_CLKS_MASK ;
	MCG->C1 |= MCG_C1_CLKS(0b01) ;
	// Select the fast or slow internal reference clock source
	MCG->C2 &= ~MCG_C2_IRCS_MASK ;
	MCG->C2 |= MCG_C2_IRCS(0b1) ;
	// internal clock devide by 1
	MCG->SC &= ~MCG_SC_FCRDIV_MASK ;
	MCG->SC |= MCG_SC_FCRDIV(0) ;
	// clock divide by 4 (OUTDIV1) - core clock = 1 Mhz
	SIM->CLKDIV1 &= ~SIM_CLKDIV1_OUTDIV1_MASK ;
	SIM->CLKDIV1 |= SIM_CLKDIV1_OUTDIV1(0b0011) ;

	// set OUTDIV4 = 0 - bus clock = 1 Mhx
	SIM->CLKDIV1 &= ~SIM_CLKDIV1_OUTDIV4_MASK ;
	SIM->CLKDIV1 |= SIM_CLKDIV1_OUTDIV4(0b0000) ;
	SystemCoreClockUpdate() ;

	// Enable clock for ADC0
	SIM->SCGC6 |= SIM_SCGC6_ADC0(1u) ;

}
void systick_init(){
	/* Program reload value*/
	SysTick->LOAD = TIMER_RElOAD_VALUE ;
	/* Clear current value*/
	SysTick->VAL = 0U ;
	/* Program Control and Status register.*/
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk ;
	/* Start Timer */
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;
}
