/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define my_usart_LIB_en// 조건식 컴파일러

#include "my_lib\my_gpio_lib.h"
#include "my_lib\my_uart_lib.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define cw1 1
#define ccw1 0

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
unsigned int speed;
char buf = 0;
uint16_t speed_control;
char x1, x2, y1, y2, z;
uint16_t step_control;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void X_go(uint16_t speed_control, uint16_t step_control)// AGV전진 , step_max 몇바퀴 돌껀지 최소 2STEP으로 설정, 약 1mm
{												  // speed_control = 8000 커질수록 느려짐
	int step;

 	 // moter direction
 	out_port(M1_DIR_GPIO_Port,M1_DIR_Pin, cw1); // m1
 	out_port(M2_DIR_GPIO_Port,M2_DIR_Pin, cw1); // m2
 	if(HAL_GPIO_ReadPin(LIMIT_X2_GPIO_Port, LIMIT_X2_Pin) == 1)
 	{
 		for(step=1; step <= step_control; step++)
		{
	      out_port(M1_CLK_GPIO_Port, M1_CLK_Pin, 1);
	      //out_port(M2_CLK_GPIO_Port, M2_CLK_Pin, 1);
	      for(speed =0; speed <= speed_control; speed++) // delay 같은 기능을 한다.
	      {
	    	// delay_loop = 10000 = 대략 = 1ms
	    	// 최소 값 = 1250 = 대략 125us
	        asm("nop");
	      }
	      out_port(M1_CLK_GPIO_Port, M1_CLK_Pin, 0);
	      //out_port(M2_CLK_GPIO_Port, M2_CLK_Pin, 0);
	      // delay_ms(1);
	      for(speed =0; speed <= speed_control; speed++)
	       {
	         asm("nop");
	       }
		}
 	}
}
void Y_go(uint16_t speed_control, uint16_t step_control)// AGV전진 , step_max 몇바퀴 돌껀지 최소 2STEP으로 설정, 약 1mm
{												  // speed_control = 8000 커질수록 느려짐
	int step;

 	 // moter direction
 	out_port(M1_DIR_GPIO_Port,M1_DIR_Pin, cw1); // m1
 	out_port(M2_DIR_GPIO_Port,M2_DIR_Pin, cw1); // m2
 	//if(HAL_GPIO_ReadPin(LIMIT_Y1_GPIO_Port, LIMIT_Y1_Pin) == 1)
 	//{
 		for(step=1; step <= step_control; step++)
		{
	      //out_port(M1_CLK_GPIO_Port, M1_CLK_Pin, 1);
	      out_port(M2_CLK_GPIO_Port, M2_CLK_Pin, 1);
	      for(speed =0; speed <= speed_control; speed++) // delay 같은 기능을 한다.
	      {
	    	// delay_loop = 10000 = 대략 = 1ms
	    	// 최소 값 = 1250 = 대략 125us
	        asm("nop");
	      }
	      //out_port(M1_CLK_GPIO_Port, M1_CLK_Pin, 0);
	      out_port(M2_CLK_GPIO_Port, M2_CLK_Pin, 0);
	      // delay_ms(1);
	      for(speed =0; speed <= speed_control; speed++)
	       {
	         asm("nop");
	       }
		}
 	//}
}
void Z_go(uint16_t speed_control, uint16_t step_control)// AGV전진 , step_max 몇바퀴 돌껀지 최소 2STEP으로 설정, 약 1mm
{												  // speed_control = 8000 커질수록 느려짐
	int step;

 	 // moter direction
 	out_port(M3_DIR_GPIO_Port,M3_DIR_Pin, cw1); // m1
 	//out_port(M2_DIR_GPIO_Port,M2_DIR_Pin, cw1); // m2

 		for(step=1; step <= step_control; step++)
		{
	      out_port(M3_CLK_GPIO_Port, M3_CLK_Pin, 1);
	      for(speed =0; speed <= speed_control; speed++) // delay 같은 기능을 한다.
	      {
	    	// delay_loop = 10000 = 대략 = 1ms
	    	// 최소 값 = 1250 = 대략 125us
	        asm("nop");
	      }
	      out_port(M3_CLK_GPIO_Port, M3_CLK_Pin, 0);
	      for(speed =0; speed <= speed_control; speed++)
	       {
	         asm("nop");
	       }
		}

}

void X_back(uint16_t speed_control, uint16_t step_control)// AGV후진 , step_max 몇바퀴 돌껀지 최소 2STEP으로 설정, 약 1mm
{												  // speed_control = 8000 커질수록 느려짐
	int step;

 	 // moter direction
 	out_port(M1_DIR_GPIO_Port, M1_DIR_Pin, ccw1); // m1
 	out_port(M2_DIR_GPIO_Port, M2_DIR_Pin, ccw1); // m2
 	if(HAL_GPIO_ReadPin(LIMIT_X1_GPIO_Port, LIMIT_X1_Pin) == 1)
 	{
 		for(step=1; step <= step_control; step++)
		{
	      out_port(M1_CLK_GPIO_Port, M1_CLK_Pin, 1);
	      //out_port(M2_CLK_GPIO_Port, M2_CLK_Pin, 1);
	      for(speed =0; speed <= speed_control; speed++) // delay 같은 기능을 한다.
	      {
	    	// delay_loop = 10000 = 대략 = 1ms
	    	// 최소 값 = 1250 = 대략 125us
	        asm("nop");
	      }
	      out_port(M1_CLK_GPIO_Port, M1_CLK_Pin, 0);
	      //out_port(M2_CLK_GPIO_Port, M2_CLK_Pin, 0);
	      // delay_ms(1);
	      for(speed =0; speed <= speed_control; speed++)
	       {
	         asm("nop");
	       }
		}
 	}
}

void Y_back(uint16_t speed_control, uint16_t step_control)// AGV후진 , step_max 몇바퀴 돌껀지 최소 2STEP으로 설정, 약 1mm
{												  // speed_control = 8000 커질수록 느려짐
	int step;

 	 // moter direction
 	out_port(M1_DIR_GPIO_Port, M1_DIR_Pin, ccw1); // m1
 	out_port(M2_DIR_GPIO_Port, M2_DIR_Pin, ccw1); // m2
 	//if(HAL_GPIO_ReadPin(LIMIT_Y2_GPIO_Port, LIMIT_Y2_Pin) == 1)
 	//{
 		for(step=1; step <= step_control; step++)
		{
	      //out_port(M1_CLK_GPIO_Port, M1_CLK_Pin, 1);
	      out_port(M2_CLK_GPIO_Port, M2_CLK_Pin, 1);

	    	  for(speed =0; speed <= speed_control; speed++) // delay 같은 기능을 한다.
	    	  {
	    		  // delay_loop = 10000 = 대략 = 1ms
	    		  // 최소 값 = 1250 = 대략 125us
	    		  asm("nop");
	    	  }
	    	  //out_port(M1_CLK_GPIO_Port, M1_CLK_Pin, 0);
	    	  out_port(M2_CLK_GPIO_Port, M2_CLK_Pin, 0);
	    	  // delay_ms(1);
	    	  for(speed =0; speed <= speed_control; speed++)
	    	  {
	    		  asm("nop");
	    	  }


		}
 	//}
}
void Z_back(uint16_t speed_control, uint16_t step_control)// AGV후진 , step_max 몇바퀴 돌껀지 최소 2STEP으로 설정, 약 1mm
{												  // speed_control = 8000 커질수록 느려짐
	int step;

 	 // moter direction
 	out_port(M3_DIR_GPIO_Port, M3_DIR_Pin, ccw1); // m1
 	//out_port(M2_DIR_GPIO_Port, M2_DIR_Pin, ccw1); // m2
 	//if(HAL_GPIO_ReadPin(LIMIT_Z_GPIO_Port, LIMIT_Z_Pin) == 1)
 	{
 		for(step=1; step <= step_control; step++) //312
		{
	      out_port(M3_CLK_GPIO_Port, M3_CLK_Pin, 1);
	      for(speed =0; speed <= speed_control; speed++) // delay 같은 기능을 한다.
	      {
	    	// delay_loop = 10000 = 대략 = 1ms
	    	// 최소 값 = 1250 = 대략 125us
	        asm("nop");
	      }
	      out_port(M1_CLK_GPIO_Port, M1_CLK_Pin, 0);
	      for(speed =0; speed <= speed_control; speed++)
	       {
	         asm("nop");
	       }
		}
 	}
}


void Start_Point(uint16_t speed_control)
{

	int step;

	    //X축 복귀  moter direction
	 	out_port(M1_DIR_GPIO_Port, M1_DIR_Pin, ccw1); // m1 (왼쪽)
	 	out_port(M2_DIR_GPIO_Port, M2_DIR_Pin, cw1);  // m2 (아래쪽)

	 		while(HAL_GPIO_ReadPin(LIMIT_X1_GPIO_Port, LIMIT_X1_Pin) == 1)
	 		{
		      out_port(M1_CLK_GPIO_Port, M1_CLK_Pin, 1);
		      for(speed =0; speed <= speed_control; speed++) // delay 같은 기능을 한다.
		      {
		    	// delay_loop = 10000 = 대략 = 1ms
		    	// 최소 값 = 1250 = 대략 125us
		        asm("nop");
		      }
		      out_port(M1_CLK_GPIO_Port, M1_CLK_Pin, 0);

		      // delay_ms(1);
		      for(speed =0; speed <= speed_control; speed++)
		       {
		         asm("nop");
		       }
	 		}

	 	HAL_Delay(1000); //1초 딜레이

	 	out_port(M1_DIR_GPIO_Port, M1_DIR_Pin, cw1); // m1
	 	while(HAL_GPIO_ReadPin(LIMIT_X1_GPIO_Port, LIMIT_X1_Pin) == 0)
	 	{
	 	  out_port(M1_CLK_GPIO_Port, M1_CLK_Pin, 1);
	 	  for(speed =0; speed <= speed_control; speed++) // delay 같은 기능을 한다.
	 	  {
	 		// delay_loop = 10000 = 대략 = 1ms
	 		// 최소 값 = 1250 = 대략 125us
	 		asm("nop");
	 	  }
	      out_port(M1_CLK_GPIO_Port, M1_CLK_Pin, 0);

	 	  // delay_ms(1);
	 	  for(speed =0; speed <= speed_control; speed++)
	 	  {
	 		asm("nop");
	 	  }
	 	}




	 	//Y축 복귀  moter direction
	 	while(HAL_GPIO_ReadPin(LIMIT_Y1_GPIO_Port, LIMIT_Y1_Pin) == 1) //Y축 원점까지 전진
	 	{
	 		for(step=1; step <= 2000; step++)
	 		{
	 			out_port(M2_CLK_GPIO_Port, M2_CLK_Pin, 1);
	 			for(speed =0; speed <= speed_control; speed++) // delay 같은 기능을 한다.
	 			{
	 				// delay_loop = 10000 = 대략 = 1ms
	 				// 최소 값 = 1250 = 대략 125us
	 				asm("nop");
	 			}
	 			out_port(M2_CLK_GPIO_Port, M2_CLK_Pin, 0);

	 			// delay_ms(1);
	 			for(speed =0; speed <= speed_control; speed++)
	 			{
	 				asm("nop");
	 			}
	 	    }
	 	}
	 	HAL_Delay(1000); //1초 딜레이
	 	out_port(M2_DIR_GPIO_Port, M2_DIR_Pin, ccw1); // m1
	 	while(HAL_GPIO_ReadPin(LIMIT_Y1_GPIO_Port, LIMIT_Y1_Pin) == 0)//
	 	{
	 		 out_port(M2_CLK_GPIO_Port, M2_CLK_Pin, 1);
	 		 for(speed =0; speed <= speed_control; speed++) // delay 같은 기능을 한다.
	 		 {
	 			 // delay_loop = 10000 = 대략 = 1ms
	 			 // 최소 값 = 1250 = 대략 125us
	 			 asm("nop");
	 		 }
	 		 out_port(M2_CLK_GPIO_Port, M2_CLK_Pin, 0);

	 		 // delay_ms(1);
	 		 for(speed =0; speed <= speed_control; speed++)
	 		 {
	 			 asm("nop");
	 		 }
	 	 }

	 		 	//Z축 복귀  moter direction
	 	while(HAL_GPIO_ReadPin(LIMIT_Z_GPIO_Port, LIMIT_Z_Pin) == 1) //Z축 원점까지 전진
	 	{
	 		for(step=1; step <= 2000; step++)
	 		{
	 		 	out_port(M3_CLK_GPIO_Port, M3_CLK_Pin, 1);
	 		 	for(speed =0; speed <= speed_control; speed++) // delay 같은 기능을 한다.
	 		 	{
	 		 		// delay_loop = 10000 = 대략 = 1ms
	 		 		// 최소 값 = 1250 = 대략 125us
	 		 		asm("nop");
	 		 	}
	 		 	out_port(M3_CLK_GPIO_Port, M3_CLK_Pin, 0);

	 		 	// delay_ms(1);
	 		 	for(speed =0; speed <= speed_control; speed++)
	 		 	{
	 		 		asm("nop");
	 		 	}
	 		}
	 	}
	 	HAL_Delay(1000); //1초 딜레이
	 	out_port(M3_DIR_GPIO_Port, M3_DIR_Pin, ccw1); // m1
	 	while(HAL_GPIO_ReadPin(LIMIT_Z_GPIO_Port, LIMIT_Z_Pin) == 0)
	 	{
	 		out_port(M3_CLK_GPIO_Port, M3_CLK_Pin, 1);
	 		for(speed =0; speed <= speed_control; speed++) // delay 같은 기능을 한다.
	 		{
	 		 	// delay_loop = 10000 = 대략 = 1ms
	 		 	// 최소 값 = 1250 = 대략 125us
	 		 	asm("nop");
	 		}
	 		out_port(M3_CLK_GPIO_Port, M3_CLK_Pin, 0);

	 		// delay_ms(1);
	 		for(speed =0; speed <= speed_control; speed++)
	 		{
	 		 	asm("nop");
	 		}
	 	}

}
/*
int ReadBit(GPIO_TypeDef *GPIOx, int pin)
{
	return ((GPIOx -> IDR) & (0x01<<pin)) > 0;
}
*/



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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  out_port(M_EN_GPIO_Port,  M_EN_Pin,  1);//stepping motor enable
  out_port(M3_EN_GPIO_Port, M3_EN_Pin, 1);//stepping motor enable
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  /*
	  x1=HAL_GPIO_ReadPin(LIMIT_X1_GPIO_Port, LIMIT_X1_Pin);
	  x2=HAL_GPIO_ReadPin(LIMIT_X1_GPIO_Port, LIMIT_X2_Pin);
	  y1=HAL_GPIO_ReadPin(LIMIT_Y2_GPIO_Port, LIMIT_Y1_Pin);
	  y2=HAL_GPIO_ReadPin(LIMIT_Y2_GPIO_Port, LIMIT_Y2_Pin);
	   z=HAL_GPIO_ReadPin(LIMIT_Z_GPIO_Port, LIMIT_Z_Pin);
	   */

	  switch(signal)
	  {
	  //수동 숫자
	  case '0': // X,Y,Z 정지
		  break;
	  case '1': X_go(8000, 2); // X축 정방향
	  	  	  	signal = '0';
		  break;
	  case '2': X_back(8000, 2);// X축 역방향
	            signal = '0';
	  	  break;
	  case '3': Y_go(8000, 2);// Y축 정방향
	            signal = '0';
		  break;
	  case '4': Y_back(8000, 2);// Y축 역방향
	            signal = '0';
	      break;
	  case '5': Z_go(8000, 2);// Z축 정방향
	            signal = '0';
	  	  break;
	  case '6': Z_back(8000, 2);// Z축 역방향
	  	  	  	signal = '0';
	  	  break;
	  //자동 숫자
	  case '7': X_go(8000, 1);// 1번창고 (1층 왼쪽 첫번째)
		  	  	HAL_Delay(500);
	            Y_back(8000, 1);
	            HAL_Delay(500);
	            Z_go(8000, 1);
	            HAL_Delay(500);



		  break;
	  case '8': // 2번창고 (1층 왼쪽 두번째)
		  break;
	  case '9': // 3번창고 (1층 왼쪽 세번째)
		  break;
	  case 'a': // 4번창고 (2층 왼쪽 첫번째)
		  break;
	  case 'b': // 5번창고 (2층 왼쪽 두번째)
		  break;
	  case 'c': // 6번창고
		  break;
	  }

	  Y_go(8000);
	  delay_ms(1000);
	  Y_back(8000);
	  delay_ms(1000);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
