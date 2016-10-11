/* Includes */
#include <stddef.h>
#include "stm32l1xx.h"


/* Private typedef */
/* Private define  */
/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */
void adc_init(void)
	  {
	//int AD_value;
	  GPIO_InitTypeDef GPIO_InitStructure;
	  ADC_InitTypeDef ADC_InitStructure;
	  /* Enable GPIO clock */
	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); //opravit a upravit
	  /* Configure ADCx Channel 2 as analog input */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
	  /* Enable the HSI oscillator */
	  RCC_HSICmd(ENABLE);
	  /* Check that HSI oscillator is ready */
	  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
	  /* Enable ADC clock */
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	  /* Initialize ADC structure */
	  ADC_StructInit(&ADC_InitStructure);
	  /* ADC1 configuration */
	  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	  ADC_InitStructure.ADC_NbrOfConversion = 1;
	  ADC_Init(ADC1, &ADC_InitStructure);
	  /* ADCx regular channel8 configuration */
	  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_16Cycles);
	  /* Enable the ADC */
	  ADC_Cmd(ADC1, ENABLE);
	  /* Wait until the ADC1 is ready */
	  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
	  {
	  }
	  /* Start ADC Software Conversion */
	  ADC_SoftwareStartConv(ADC1);
	  }

void LED_init(void){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIOinitS;
	GPIOinitS.GPIO_Pin = GPIO_Pin_5;
	GPIOinitS.GPIO_Mode = GPIO_Mode_OUT;
	GPIOinitS.GPIO_OType = GPIO_OType_PP;
	GPIOinitS.GPIO_PuPd = GPIO_PuPd_UP;
	GPIOinitS.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIOA, &GPIOinitS);
}

int main(void)
{
  int i = 0;
  int AD_value;

  adc_init();
  LED_init();
  /* Infinite loop */
  //Spustenie prevodu:
  	  /* Start ADC Software Conversion */
  while(1){
	  ADC_SoftwareStartConv(ADC1);
  	  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)){}
  	  AD_value=ADC_GetConversionValue(ADC1);
    	  }
	return 0;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*
 * Minimal __assert_func used by the assert() macro
 * */
void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
void __assert(const char *file, int line, const char *failedexpr)
{
   __assert_func (file, line, NULL, failedexpr);
}
