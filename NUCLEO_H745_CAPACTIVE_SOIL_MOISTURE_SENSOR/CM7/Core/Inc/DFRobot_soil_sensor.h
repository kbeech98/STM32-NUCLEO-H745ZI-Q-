/*
 * DFRobot_soil_moisture_sensor.h
 *
 *  Created on: Nov. 20, 2021
 *      Author: Kristian Beech
 */

#include "stm32h7xx_hal.h"

#define SOIL_SENS1_PORT GPIOA
#define SOIL_SENS1_PIN GPIO_PIN_6

#define SOIL_SENS2_PORT GPIOC
#define SOIL_SENS2_PIN GPIO_PIN_4

#ifndef INC_DFROBOT_SOIL_MOISTURE_SENSOR_H_
#define INC_DFROBOT_SOIL_MOISTURE_SENSOR_H_


void poll_SOIL_SENSOR(void);

#endif /* INC_DFROBOT_SOIL_MOISTURE_SENSOR_H_ */
