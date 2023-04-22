/*
 * lcd.c
 *
 *  Created on: Feb 19, 2023
 *      Author: Connor
 */

#include <timers.h>
#include <shift_register.h>
#include <lcd.h>
#include "stm32f0xx_hal.h"

// Define pins

#define RS_PIN GPIO_PIN_10
#define RS_PORT GPIOB

#define E_PIN GPIO_PIN_4
#define E_PORT GPIOB

// Define timer
/*#define timer htim1

extern TIM_HandleTypeDef timer;
void delay(uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&timer, 0);
	while(__HAL_TIM_GET_COUNTER(&timer) < us);
}*/

void lcd_send_cmd(char data)
{
	HAL_GPIO_WritePin(RS_PORT, RS_PIN, 0);

	// write data to lcd register
	shift_out(data);

	// latch data
	HAL_GPIO_WritePin(E_PORT, E_PIN, 1);
	micro_delay(2);
	//HAL_Delay(100);
	HAL_GPIO_WritePin(E_PORT, E_PIN, 0);
	micro_delay(2);
	//HAL_Delay(100);
}

void lcd_send_data(char data)
{
	HAL_GPIO_WritePin(RS_PORT, RS_PIN, 1);

	// write data to lcd register
	shift_out(data);

	// latch data
	HAL_GPIO_WritePin(E_PORT, E_PIN, 1);
	micro_delay(2);
	//HAL_Delay(100);
	HAL_GPIO_WritePin(E_PORT, E_PIN, 0);
	micro_delay(2);
	//HAL_Delay(100);
}

void lcd_clear_display()
{
	lcd_send_cmd(0x01);
	HAL_Delay(2);
}

void lcd_return_home()
{
	lcd_send_cmd(0x02);
	HAL_Delay(1);
}

void lcd_initialize()
{
	HAL_Delay(50);
	lcd_send_cmd(0x38);		// initialize in 8-bit mode, 4 lines
	HAL_Delay(5);
	lcd_clear_display();
	lcd_return_home();
	lcd_send_cmd(0x0C);		// turn on display
	HAL_Delay(5);
}

void lcd_print(char *str) {
	while(*str) lcd_send_data(*str++);
}

void lcd_put_cursor(int row, int col)
{
	int row_address;

	switch(row)		// correct row order
	{
	case 0:
		row_address = 0;
		break;
	case 1:
		row_address = 0x40;
		break;
	case 2:
		row_address = 0x14;
		break;
	case 3:
		row_address = 0x54;
		break;
	default:
		break;
	}

	int address;
	address = (0x7F)&(row_address + col);

	lcd_send_cmd((0x80)|address);	// set DDRAM address
}
