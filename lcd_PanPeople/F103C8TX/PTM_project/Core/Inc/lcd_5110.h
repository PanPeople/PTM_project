/*
 * lcd_5110.h
 *
 *  Created on: May 30, 2021
 *      Author: PanPeople
 */

#ifndef INC_LCD_5110_H_
#define INC_LCD_5110_H_

#define LCD_X 84
#define LCD_Y 48

#define LCD_C GPIO_PIN_RESET//<- command
#define LCD_D GPIO_PIN_SET// <- data



#define LCD_DC_PIN GPIO_PIN_1
#define LCD_CE_PIN GPIO_PIN_6
#define LCD_RST_PIN GPIO_PIN_0

#define LCD_DC_PORT GPIOB
#define LCD_CE_PORT GPIOA
#define LCD_RST_PORT GPIOB






void LCD_Initialize(SPI_HandleTypeDef *spi);
void LCD_Command(SPI_HandleTypeDef *spi,uint8_t cmd);
void LCD_Data(SPI_HandleTypeDef *spi,uint8_t* cmd);
void LCD_Clear(SPI_HandleTypeDef *spi);
void LCD_Fill(SPI_HandleTypeDef *spi);
void LCD_draw_pixel(uint8_t buffer[],uint8_t x, uint8_t y);//to save cycles, after this it is required to use LCD_Refresh();
void LCD_Draw_Line(SPI_HandleTypeDef *spi);
void LCD_Printf(SPI_HandleTypeDef *spi);
void LCD_Clear_Buffer(uint8_t buffer[]);
void LCD_Data_Byte(SPI_HandleTypeDef *spi,uint8_t* cmd);

void lcd_data(SPI_HandleTypeDef *spi,const uint8_t* data);
void lcd_draw_text(int row, int col, const char* text,uint8_t buffer[]);

extern const uint8_t logo[];
/*
 7-17-2011
 Spark Fun Electronics 2011
 Nathan Seidle

 This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

 This code writes a series of images and text to the Nokia 5110 84x48 graphic LCD:
 http://www.sparkfun.com/products/10168

 Do not drive the backlight with 5V. It will smoke. However, the backlight on the LCD seems to be
 happy with direct drive from the 3.3V regulator.
 Although the PCD8544 controller datasheet recommends 3.3V, the graphic Nokia 5110 LCD can run at 3.3V or 5V.
 No resistors needed on the signal lines.

 You will need 5 signal lines to connect to the LCD, 3.3 or 5V for power, 3.3V for LED backlight, and 1 for ground.
 
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Nathan Seidle wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Nathan Seidle
 * ----------------------------------------------------------------------------
 */
extern const uint8_t font_ASCII[][5];

#endif /* INC_LCD_5110_H_ */
