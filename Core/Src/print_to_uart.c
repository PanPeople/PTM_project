/*
 * print_to_uart.c
 *
 *  Created on: Jun 15, 2021
 *      Author: Damian
 */

#include "usart.h"

int __io_putchar3(int ch)
{
	HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 1000);
	return ch;
}

