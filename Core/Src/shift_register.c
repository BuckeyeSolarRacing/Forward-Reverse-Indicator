/*
 * shift_register.c
 *
 *  Created on: Feb 19, 2023
 *      Author: Connor
 */

#include <shift_register.h>
#include "stm32f0xx_hal.h"

// Pin definitions

#define SER_PIN GPIO_PIN_10
#define SER_PORT GPIOA

#define CLK_PIN GPIO_PIN_3
#define CLK_PORT GPIOB

// Function definition

void shift_out(int data)
{
	int i;
	for(i = 0; i < 8; i++)
	{
		HAL_GPIO_WritePin(SER_PORT, SER_PIN, ((data>>(7-i))&0x01));
		HAL_GPIO_WritePin(CLK_PORT, CLK_PIN, 1);
		HAL_GPIO_WritePin(CLK_PORT, CLK_PIN, 0);
	}
	HAL_GPIO_WritePin(CLK_PORT, CLK_PIN, 1);
	HAL_GPIO_WritePin(CLK_PORT, CLK_PIN, 0);
}
