//-KB,-5-11-202-
//dht11_temp_sensor.h

float Temperature;
float Humidity;

//Define the DHT11 pin below
#define DHT11_PORT GPIOD
#define DHT11_PIN GPIO_PIN_0

#ifndef INC_dht11_temp_sensor_H_
#define INC_dht11_temp_sensor_H_

#include "stm32h7xx_hal.h"
#include "stdio.h"

void us_delay(uint16_t us);

void delay_TEST (void);

void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void DHT11_Start (void);

uint8_t DHT11_Read (void);

uint8_t DHT11_Check_Response (void);

void poll_DHT11(void);

#endif /* INC_dht11_temp_sensor_H_ */
