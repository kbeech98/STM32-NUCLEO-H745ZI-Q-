/*
 * DFRobot_soil_moisture_sensor.c
 *
 *  Created on: Nov. 20, 2021
 *      Author: Kristian Beech
 */

#include "DFRobot_soil_sensor.h"

/*void poll_SOIL_SENSOR(void) //tried using dma but didnt work.. will revisit
{
	//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14); //Debugging LED
	//SCB_InvalidateDCache_by_Addr((uint32_t*)(((uint32_t)SoilSensor) & ~(uint32_t)0x1F), RX_LENGTH+32);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)SoilSensor, RX_LENGTH);
	//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14); //Debugging LED
	while(adcConversionComplete == 0)
	{

	}
	adcConversionComplete = 0;	//clear conversion complete flag
	//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14); //Debugging LED
	//SCB_CleanDCache_by_Addr((uint32_t*)(((uint32_t)SoilSensor) & ~(uint32_t)0x1F), RX_LENGTH+32);
}*/

void poll_SOIL_SENSOR_1_2(void)
{
	  ADC_Select_CH3();	//poll sensor 1 on pin PB1
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, 1000);
	  SoilSensor1 = HAL_ADC_GetValue(&hadc1);
	  HAL_ADC_Stop(&hadc1);

	  ADC_Select_CH5(); //poll sensor 2 on pin PA6
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, 1000);
	  SoilSensor2 = HAL_ADC_GetValue(&hadc1);
	  HAL_ADC_Stop(&hadc1);
}

void ADC_Select_CH3 (void)
{
	ADC_ChannelConfTypeDef sConfig = {0};

	  sConfig.Channel = ADC_CHANNEL_3;
	  sConfig.Rank = ADC_REGULAR_RANK_1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
	  sConfig.SingleDiff = ADC_SINGLE_ENDED;
	  sConfig.OffsetNumber = ADC_OFFSET_NONE;
	  sConfig.Offset = 0;
	  sConfig.OffsetSignedSaturation = DISABLE;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
		  __disable_irq(); //Error handler function in main
		  while (1)
		  {
		  }
	  }
}

void ADC_Select_CH5 (void)
{
	ADC_ChannelConfTypeDef sConfig = {0};

	  sConfig.Channel = ADC_CHANNEL_5;
	  sConfig.Rank = ADC_REGULAR_RANK_1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
	  sConfig.SingleDiff = ADC_SINGLE_ENDED;
	  sConfig.OffsetNumber = ADC_OFFSET_NONE;
	  sConfig.Offset = 0;
	  sConfig.OffsetSignedSaturation = DISABLE;

	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
		  __disable_irq(); //Error handler function in main
		  while (1)
		  {
		  }
	  }
}




