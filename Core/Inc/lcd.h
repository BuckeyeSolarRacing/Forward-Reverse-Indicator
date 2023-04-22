/*
 * lcd.h
 *
 *  Created on: Feb 19, 2023
 *      Author: Connor
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

void lcd_send_cmd(char data);

void lcd_send_data(char data);

void lcd_clear_display();

void lcd_return_home();

void lcd_initialize();

void lcd_print(char *str);

void lcd_put_cursor(int row, int col);

#endif /* INC_LCD_H_ */
