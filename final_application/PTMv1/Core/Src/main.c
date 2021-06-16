/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "MS5837.h"
#include "printf_to_uart.h"
#include "lcd_5110.h"
#include "lcd_i2c.h"
#include <stdbool.h>
#include <stdio.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

//buffer for 5510

uint8_t buffer[LCD_X*LCD_Y/2];


uint8_t flag [3] = {0,0,0};
//flag:
//flag[0] <- timer update
//flag[1] <- buffer has been drawn
//flag[2] <- direction "0" for outside/left "1" for inside/right animation



//uint8_t dron [][]={
//		{0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0}
//		     ,{1,1}			   ,{4,1}		     ,{7,1}
//			 ,{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},
//		{0,3}	   ,{2,3},{3,3},{4,3},{5,3},{6,3},{7,3},{8,3},
//		{0,4}	   ,{2,4},{3,4},{4,4},{5,4},{6,4},{7,4},{8,4}
//		 	 ,{1,5},{2,5},{3,5},{4,5},{5,5},{6,5},{7,5}
//			 ,{1,6}			   ,{4,6}		     ,{7,6},
//		{0,7},{1,7},{2,7},{3,7},{4,7},{5,7},{6,7},{7,7},{8,7}
//
//};
uint8_t dron [27*2][2]={
				{0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0}
				     ,{1,1}			   ,{4,1}		     ,{7,1}
					 ,{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2},
				{0,3}	   ,{2,3},{3,3},{4,3},{5,3},{6,3},{7,3},{8,3},
				{0,4}	   ,{2,4},{3,4},{4,4},{5,4},{6,4},{7,4},{8,4}
				 	 ,{1,5},{2,5},{3,5},{4,5},{5,5},{6,5},{7,5}
					 ,{1,6}			   ,{4,6}		     ,{7,6},
				{0,7},{1,7},{2,7},{3,7},{4,7},{5,7},{6,7},{7,7},{8,7}
};

const uint8_t template [] = {
0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x22, 0x22, 0x22,
0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
0xFF, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};


//to corect

uint8_t depth = 20;
uint16_t preasure = 2137;


//global variable
uint8_t sign;
uint8_t message[20];
uint8_t message1[20];
uint16_t msg_length;

struct lcd_disp disp;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);

//print to UART
int __io_putchar(int ch)
{
	HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 1000);
	return ch;
}


/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	//cls buffer
	LCD_Clear_Buffer(buffer);

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */

  //time start & init
  HAL_TIM_Base_Start_IT(&htim1);

     LCD_Initialize(&hspi1);


  //buffor for LCD_5510 startup screen

     for (uint16_t i = 0; i< LCD_X*LCD_Y/8 ; i++){
   	  buffer[i] = logo[i];
     }

     lcd_draw_text(0, 60, "v0.9", buffer);


  //push to display form buffer

     LCD_Data(&hspi1, buffer);

     HAL_Delay(1000);

     uint8_t r = 20; //high of submarine visualization


   //some wierd shit, badapple
     for (uint16_t i = 0; i< LCD_X*LCD_Y/8 ; i++){
   	  buffer[i] = template[i];
     }



  //BAR02 init
  int a = 0;
  MS5837_init(&hi2c1);


  if(HAL_I2C_Init(&hi2c1) == HAL_OK) {
  	  printf("\n\r HAL_OK INIT\n\r\n\r");
    }

  while (!MS5837_init) {
  	    	  printf("Init failed!");
  	    	  printf("Are SDA/SCL connected correctly?");
  	    	  printf("Blue Robotics Bar02: White=SDA, Green=SCL");
  	    	  printf("\n\n\n");
  	    	HAL_Delay(2000);
  	      }



  //getting one character in the interrupt mode
  HAL_UART_Receive_IT(&huart1, &sign, 1);

  disp.addr = (0x27 << 1);
  disp.bl = true;
  lcd_init(&disp);
  sprintf((char*)disp.f_line, "First line of text");
  sprintf((char*)disp.s_line, "Second line of text");
  sprintf((char*)disp.t_line, "Third line of text");
  sprintf((char*)disp.l_line, "Last line of text");
  HAL_Delay(500);
  	  lcd_display(&disp);


  sprintf((char*)disp.f_line, "*");
  HAL_Delay(500);
  	  lcd_display(&disp);

  sprintf((char*)disp.s_line, "**");
  HAL_Delay(500);
  	  lcd_display(&disp);

  sprintf((char*)disp.t_line, "***");
  HAL_Delay(500);
  	  lcd_display(&disp);

  sprintf((char*)disp.l_line, "****");
  HAL_Delay(500);
  	  lcd_display(&disp);



	sprintf((char*)disp.f_line, " ");
	sprintf((char*)disp.s_line, " ");
	sprintf((char*)disp.t_line, " ");
	sprintf((char*)disp.l_line, "     KN ROBOCIK");
	HAL_Delay(1500);
		lcd_display(&disp);




  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {






	  if(flag[1] == 0){


	  		  flag[0] = 0;

	  			for(uint16_t i = 0; i < (LCD_X*LCD_Y/8); i ++){
	  				buffer[i]= 0x00;
	  			}

	  			  for (uint16_t i = 0; i< LCD_X*LCD_Y/8 ; i++){
	  				  buffer[i] = template[i];
	  			  }

	  			for(uint8_t x = 0 ; x < LCD_X ; x++ ){
	  			  LCD_draw_pixel(buffer,x, 0);
	  			  LCD_draw_pixel(buffer,x, LCD_Y);
	  			}


	  			for(uint8_t y = 0 ; y < LCD_X ; y++ ){
	  			  LCD_draw_pixel(buffer,0, y);
	  			  LCD_draw_pixel(buffer,LCD_X, y);
	  			}



	  			for(uint8_t i = 0; i< 54 ; i ++){
	  				LCD_draw_pixel(buffer,dron[i][0]+ 11 , dron[i][1]+r);
	  			}

	  			  lcd_draw_text(1, 25, "Preasure:", buffer);
	  			  char tmp[16];
	  			  sprintf(tmp, "%d hPa", preasure);
	  			  lcd_draw_text(2, 25,tmp, buffer);
	  			  lcd_draw_text(3, 25, "Depth:", buffer);
	  			  sprintf(tmp, "%d m", depth);
	  			  lcd_draw_text(4, 25,tmp, buffer);


	  	  	  flag[1]=1;


	  	  }



	  	  if(flag[0] == 1 && flag[1]== 1) {
	  		  LCD_Data(&hspi1, buffer);
	  		    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	  		  flag[1] = 0;

	  	  }




	  a++;
	 	  MS5837_read();


	 	  depth = MS5837_depth();
	 	  preasure = MS5837_pressure(1);


	  	  printf("Nr: %i \n\r",a);

	  	   printf("Pressure: %i mbar \n\r",preasure);

	  	   printf("Temperature: %4.3f deg C \n\r",MS5837_temperature());

	  	   printf("Depth: %i m \n\r",depth);

	  	   printf("Altitude: %4.3f above mean sea level \n\r\n\r",MS5837_altitude());


	  	 	  HAL_Delay(1000);



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

// LED blinking
	  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); //LD1_Pin

	  HAL_Delay(500);





  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* TIM1_UP_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM1_UP_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);
}

/* USER CODE BEGIN 4 */


// don't do

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

	if(htim->Instance == TIM1){

		flag[0] = 1;
	}

}




// UART communications fun and play

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	{
	if (huart->Instance == USART1) //check for UART1
		{
		if(sign == 'D')
			{
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
				msg_length = sprintf(message, "LED ON\n\r");
			}
		else if (sign == 'K')
			{
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
				msg_length = sprintf(message, "LED OFF\n\r");
			}
		else
			{
				msg_length = sprintf(message, "BAD SIGN\n\r");
			}
		HAL_UART_Transmit_IT(&huart1, message, msg_length); //wait for next sign
		HAL_UART_Receive_IT(&huart1, &sign, 1); //wait for next sign
		}
	}



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
