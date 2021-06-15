/*
 * lcd_i2c.c
 *
 *  Created on: Jun 15, 2021
 *      Author: Damian
 */


#include "lcd_i2c.h"
#include "lcd_chars.h"
#include "stm32f1xx_hal.h"
#include "i2c.h"




void lcd_init(struct lcd_disp * lcd)
{
	uint8_t xpin = 0;
	/* set backlight */
	if(lcd->bl)
	{
		xpin = BL_PIN;
	}

	/* init sequence */
	HAL_Delay(40);
	lcd_write(lcd->addr, INIT_8_BIT_MODE, xpin);
	HAL_Delay(5);
	lcd_write(lcd->addr, INIT_8_BIT_MODE, xpin);
	HAL_Delay(1);
	lcd_write(lcd->addr, INIT_8_BIT_MODE, xpin);

	/* set 4-bit mode */
	lcd_write(lcd->addr, INIT_4_BIT_MODE, xpin);
	HAL_Delay(5);

	/* set cursor mode */
	lcd_write(lcd->addr, UNDERLINE_OFF_BLINK_OFF, xpin);
	HAL_Delay(5);

	/* clear */
	lcd_clear(lcd);

}

void lcd_write(uint8_t addr, uint8_t data, uint8_t xpin)
{
	uint8_t tx_data[4];

	/* split data */
	tx_data[0] = (data & 0xF0) | EN_PIN | xpin;
	tx_data[1] = (data & 0xF0) | xpin;
	tx_data[2] = (data << 4) | EN_PIN | xpin;
	tx_data[3] = (data << 4) | xpin;

	/* send data via i2c */
	HAL_I2C_Master_Transmit(&HI2C_DEF, addr, tx_data, 4, 100);

	HAL_Delay(1);
}

void lcd_display(struct lcd_disp * lcd)
{
	uint8_t xpin = 0, i = 0;
	char ch;

	/* set backlight */
	if(lcd->bl)
	{
		xpin = BL_PIN;
	}

	lcd_clear(lcd);

	/* send first line data */
	lcd_write(lcd->addr, FIRST_CHAR_LINE_1, xpin);
	while(lcd->f_line[i])
	{
		if (ch < 9)
		{
			ch--;
		}
		lcd_write(lcd->addr, lcd->f_line[i], (xpin | RS_PIN));
		i++;
	}

	/* send second line data */
	i = 0;
	lcd_write(lcd->addr, FIRST_CHAR_LINE_2, xpin);
	while(lcd->s_line[i])
	{
		if (ch < 9)
		{
			ch--;
		}
		lcd_write(lcd->addr, lcd->s_line[i], (xpin | RS_PIN));
		i++;
	}

	/* send first line data */
	i = 0;
	lcd_write(lcd->addr, FIRST_CHAR_LINE_3, xpin);
	while(lcd->t_line[i])
	{
		if (ch < 9)
		{
			ch--;
		}
		lcd_write(lcd->addr, lcd->t_line[i], (xpin | RS_PIN));
		i++;
	}

	/* send second line data */
	i = 0;
	lcd_write(lcd->addr, FIRST_CHAR_LINE_4, xpin);
	while(lcd->l_line[i])
	{
		if (ch < 9)
		{
			ch--;
		}
		lcd_write(lcd->addr, lcd->l_line[i], (xpin | RS_PIN));
		i++;
	}


}

void lcd_clear(struct lcd_disp * lcd)
{
	uint8_t xpin = 0;

	/* set backlight */
	if(lcd->bl)
	{
		xpin = BL_PIN;
	}

	/* clear display */
	lcd_write(lcd->addr, CLEAR_LCD, xpin);
	HAL_Delay(2);
}



void lcd_prog(struct lcd_disp * lcd)
{
	uint8_t xpin = 0, i, j;

	/* set backlight */
	if(lcd->bl)
	{
		xpin = BL_PIN;
	}

	/* send 8 custom chars */
	lcd_write(lcd->addr, (CG_FIRST_CHAR), xpin);
	for(i = 0; i <= 7; i++)
	{
		for(j = 0; j <= 7; j ++)
		{
			lcd_write(lcd->addr, (user_chars[i][j]), (xpin | RS_PIN));
		}
	}
}





