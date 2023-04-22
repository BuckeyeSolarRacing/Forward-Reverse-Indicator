/*
 * timers.c
 *
 *  Created on: Feb 20, 2023
 *      Author: Connor
 */

#include <timers.h>
#include "stm32f0xx_hal.h"

// Define timer
#define timer htim1

extern TIM_HandleTypeDef timer;
void micro_delay(int us)		// microsecond delay function definition
{
	__HAL_TIM_SET_COUNTER(&timer, 0);
	while(__HAL_TIM_GET_COUNTER(&timer) < us);
}
