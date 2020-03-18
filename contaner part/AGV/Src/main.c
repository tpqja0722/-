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
unsigned char sensor1,sensor2,sensor3,sensor4,sensor5,sensor6;
unsigned int BI;
unsigned int BI1;
unsigned int BI2;
unsigned char Final_sensor;
unsigned int speed;
char buf = 0;
uint16_t speed_control;
uint16_t step_z;
char x1, x2, y1, y2, z;
uint16_t step_control;
int step;
int cnt123;
uint8_t Bluetooth;

uint8_t lens;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void sensor_check (void)
{
	BI = (0xfc00&(byte_rd_H(GPIOC)));
	BI1 = BI >> 10;
	BI2 = (0x3f & BI1);
	sensor6 = BI2/32%2;
    sensor5 = BI2/16%2;
    sensor4 = BI2/8%2;
    sensor3 = BI2/4%2;
    sensor2 = BI2/2%2;
    sensor1 = BI2%2;
    /*tx("s", 2);
	tx_send(',', 2);
	tx_send(sensor1 + 0x30, 2);       //5번센서
	tx_send(',', 2);
	tx_send(sensor2 + 0x30, 2);       //4번센서
	tx_send(',', 2);
	tx_send(sensor3 + 0x30, 2);       //3번센서
	tx_send(',', 2);
	tx_send(sensor4 + 0x30, 2);       //2번센서
	tx_send(',', 2);
	tx_send(sensor5 + 0x30, 2);       //1번센서
	tx("\r\n", 2);*/

}

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
	      out_port(M3_CLK_GPIO_Port, M3_CLK_Pin, 0);
	      for(speed =0; speed <= speed_control; speed++)
	       {
	         asm("nop");
	       }
		}
 	}
}

void Load (void)
{
	Z_go(8000, 11000);
	HAL_Delay(1000);
	Y_go(8000, 7777);
    HAL_Delay(500);
    Z_back(8000, 11000);
    HAL_Delay(1000);
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

	 /*	out_port(M1_DIR_GPIO_Port, M1_DIR_Pin, cw1); // m1
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
	 	*/




	 	//Y축 복귀  moter direction
	 	while(HAL_GPIO_ReadPin(LIMIT_Y1_GPIO_Port, LIMIT_Y1_Pin) == 1) //Y축 원점까지 전진
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
	 	HAL_Delay(1000); //1초 딜레이
	 	/*out_port(M2_DIR_GPIO_Port, M2_DIR_Pin, ccw1); // m1
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
*/
	 	 	//Z축 복귀  moter direction
	 	out_port(M3_DIR_GPIO_Port, M3_DIR_Pin, ccw1); // m1
	 	while(HAL_GPIO_ReadPin(LIMIT_Z_GPIO_Port, LIMIT_Z_Pin) == 1) //Z축 원점까지 전진
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
	 	HAL_Delay(1000); //1초 딜레이
	 /*	out_port(M3_DIR_GPIO_Port, M3_DIR_Pin, cw1); // m1
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
*/
}
void in_out(void)
{
	Y_back(6000,200);
	delay_ms(500);
	Z_go(6000,8000);
	delay_ms(500);
	Y_go(6000,150);
	delay_ms(500);
	Z_back(6000,8000);
	delay_ms(500);


}
void out_in(void)
{
	Z_go(6000,8000);
	delay_ms(500);
	Y_back(6000,500);
	delay_ms(500);
	Z_back(6000,8000);
	delay_ms(500);
	//Y_back(6000,500);
	//delay_ms(500);

}
void ch_1_in(void)
{

	while(HAL_GPIO_ReadPin(LIMIT_X1_GPIO_Port, LIMIT_X1_Pin) == 1)
	{
			X_back(6000,2);
	}
	delay_ms(500);

		Y_back(6000,900);//agv의 위치 조정
		delay_ms(500);
		out_in();
	while(HAL_GPIO_ReadPin(LIMIT_Y1_GPIO_Port, LIMIT_Y1_Pin) == 1)
		{
			Y_go(6000,2);
		}
	while(HAL_GPIO_ReadPin(LIMIT_X2_GPIO_Port, LIMIT_X2_Pin) == 1)
	{
		X_go(6000,2);
	}
	delay_ms(500);
	Y_back(8000,1750);
	delay_ms(500);
	in_out();
	delay_ms(500);
	Start_Point(8000);
	Bluetooth = 'g';
}
void ch_3_in(void)
{

	while(HAL_GPIO_ReadPin(LIMIT_X1_GPIO_Port, LIMIT_X1_Pin) == 1)
	{
			X_back(6000,2);
	}
	delay_ms(500);

		Y_back(6000,500);//agv의 위치 조정
		delay_ms(500);
		out_in();
	while(HAL_GPIO_ReadPin(LIMIT_Y1_GPIO_Port, LIMIT_Y1_Pin) == 1)
		{
			Y_go(6000,2);
		}
		X_go(6000,7440);
	delay_ms(500);
	Y_back(8000,1700);
	delay_ms(500);
	in_out();
	delay_ms(500);
	Start_Point(8000);

}
void ch_5_in(void)
{

	while(HAL_GPIO_ReadPin(LIMIT_X1_GPIO_Port, LIMIT_X1_Pin) == 1)
	{
			X_back(6000,2);
	}
	delay_ms(500);

		Y_back(6000,500);//agv의 위치 조정
		delay_ms(500);
		out_in();
	while(HAL_GPIO_ReadPin(LIMIT_Y1_GPIO_Port, LIMIT_Y1_Pin) == 1)
		{
			Y_go(6000,2);
		}
	X_go(6000,4000);
	delay_ms(500);
	Y_back(8000,1700);
	delay_ms(500);
	in_out();
	delay_ms(500);
	Start_Point(8000);
}
void ch_2_in(void)
{

	while(HAL_GPIO_ReadPin(LIMIT_X1_GPIO_Port, LIMIT_X1_Pin) == 1)
	{
			X_back(6000,2);
	}
	delay_ms(500);

		Y_back(6000,500);//agv의 위치 조정
		delay_ms(500);
		out_in();
	while(HAL_GPIO_ReadPin(LIMIT_Y1_GPIO_Port, LIMIT_Y1_Pin) == 1)
		{
			Y_go(6000,2);
		}
	while(HAL_GPIO_ReadPin(LIMIT_X2_GPIO_Port, LIMIT_X2_Pin) == 1)
	{
		X_go(6000,2);
	}
	delay_ms(500);
	Y_back(8000,200);
	delay_ms(500);
	in_out();
	delay_ms(500);
	Start_Point(8000);
}
void ch_4_in(void)
{

	while(HAL_GPIO_ReadPin(LIMIT_X1_GPIO_Port, LIMIT_X1_Pin) == 1)
	{
			X_back(6000,2);
	}
	delay_ms(500);

		Y_back(6000,500);//agv의 위치 조정
		delay_ms(500);
		out_in();
	while(HAL_GPIO_ReadPin(LIMIT_Y1_GPIO_Port, LIMIT_Y1_Pin) == 1)
		{
			Y_go(6000,2);
		}
		X_go(6000,7440);
	delay_ms(500);
	Y_back(8000,200);
	delay_ms(500);
	in_out();
	delay_ms(500);
	Start_Point(8000);
}
void ch_6_in(void)
{

	while(HAL_GPIO_ReadPin(LIMIT_X1_GPIO_Port, LIMIT_X1_Pin) == 1)
	{
			X_back(6000,2);
	}
	delay_ms(500);

		Y_back(6000,500);//agv의 위치 조정
		delay_ms(500);
		out_in();
	while(HAL_GPIO_ReadPin(LIMIT_Y1_GPIO_Port, LIMIT_Y1_Pin) == 1)
		{
			Y_go(6000,2);
		}
	X_go(6000,4000);
	delay_ms(500);
	Y_back(8000,200);
	delay_ms(500);
	in_out();
	delay_ms(500);
	Start_Point(8000);
}
void ch_1_out(void)
{

	while(HAL_GPIO_ReadPin(LIMIT_X2_GPIO_Port, LIMIT_X2_Pin) == 1)
	{
			X_go(6000,2);
	}
	delay_ms(500);

		Y_back(6000,1750);
		delay_ms(500);
		in_out();
	while(HAL_GPIO_ReadPin(LIMIT_Y1_GPIO_Port, LIMIT_Y1_Pin) == 1)
		{
			Y_go(6000,2);
		}
	while(HAL_GPIO_ReadPin(LIMIT_X1_GPIO_Port, LIMIT_X1_Pin) == 1)
	{
		X_back(6000,2);
	}
	delay_ms(500);
	Y_back(8000,900);//agv의위치
	delay_ms(500);
	out_in();
	delay_ms(500);
	Start_Point(8000);
	Bluetooth = 'g';
}
void ch_3_out(void)
{


		X_go(12000,7440);

		delay_ms(500);

		Y_back(6000,1700);
			delay_ms(500);
			out_in();
		while(HAL_GPIO_ReadPin(LIMIT_Y1_GPIO_Port, LIMIT_Y1_Pin) == 1)
			{
				Y_go(6000,2);
			}
		while(HAL_GPIO_ReadPin(LIMIT_X1_GPIO_Port, LIMIT_X1_Pin) == 1)
		{
			X_back(6000,2);
		}
		delay_ms(500);
		Y_back(8000,800);//agv의위치
		delay_ms(500);
		in_out();
		delay_ms(500);
		Start_Point(8000);
}
void ch_5_out(void)
{


		X_go(12000,4040);

		delay_ms(500);

		Y_back(6000,1700);
			delay_ms(500);
			out_in();
		while(HAL_GPIO_ReadPin(LIMIT_Y1_GPIO_Port, LIMIT_Y1_Pin) == 1)
			{
				Y_go(6000,2);
			}
		while(HAL_GPIO_ReadPin(LIMIT_X1_GPIO_Port, LIMIT_X1_Pin) == 1)
		{
			X_back(6000,2);
		}
		delay_ms(500);
		Y_back(8000,800);//agv의위치
		delay_ms(500);
		in_out();
		delay_ms(500);
		Start_Point(8000);
}
void ch_2_out(void)
{

	while(HAL_GPIO_ReadPin(LIMIT_X2_GPIO_Port, LIMIT_X2_Pin) == 1)
	{
			X_go(6000,2);
	}
	delay_ms(500);

		Y_back(6000,200);
		delay_ms(500);
		in_out();
	while(HAL_GPIO_ReadPin(LIMIT_Y1_GPIO_Port, LIMIT_Y1_Pin) == 1)
		{
			Y_go(6000,2);
		}
	while(HAL_GPIO_ReadPin(LIMIT_X1_GPIO_Port, LIMIT_X1_Pin) == 1)
	{
		X_back(6000,2);
	}
	delay_ms(500);
	Y_back(8000,800);//agv의위치
	delay_ms(500);
	out_in();
	delay_ms(500);
	Start_Point(8000);
}
void ch_4_out(void)
{


		X_go(12000,7440);

		delay_ms(500);

		Y_back(6000,200);
			delay_ms(500);
			out_in();
		while(HAL_GPIO_ReadPin(LIMIT_Y1_GPIO_Port, LIMIT_Y1_Pin) == 1)
			{
				Y_go(6000,2);
			}
		while(HAL_GPIO_ReadPin(LIMIT_X1_GPIO_Port, LIMIT_X1_Pin) == 1)
		{
			X_back(6000,2);
		}
		delay_ms(500);
		Y_back(8000,800);//agv의위치
		delay_ms(500);
		in_out();
		delay_ms(500);
		Start_Point(8000);
}
void ch_6_out(void)
{


		X_go(12000,4040);

		delay_ms(500);

		Y_back(6000,200);
			delay_ms(500);
			out_in();
		while(HAL_GPIO_ReadPin(LIMIT_Y1_GPIO_Port, LIMIT_Y1_Pin) == 1)
			{
				Y_go(6000,2);
			}
		while(HAL_GPIO_ReadPin(LIMIT_X1_GPIO_Port, LIMIT_X1_Pin) == 1)
		{
			X_back(6000,2);
		}
		delay_ms(500);
		Y_back(8000,800);//agv의위치
		delay_ms(500);
		in_out();
		delay_ms(500);
		Start_Point(8000);
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
int _write(int file, unsigned char* p, int len)
{
  HAL_UART_Transmit(&huart1, p, len, 1);
  return len;
}

// usart RX INT func
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart -> Instance == USART1)
   {
	 // uart 1 rx int == pc system
     if(Rx_data_1[0] == CR)
      {
       	rx_end_flag_1 = 1;
       	rx_cnt_1 = 0;
      }
     else
      {
    	Rx_data_1[rx_cnt_1++] = Rx_data_1[0];
      }

      Bluetooth = Rx_data_1[0];
      tx_send(Rx_data_1[0],1);


	  // init flag clr
	   __HAL_UART_CLEAR_PEFLAG(&huart1);

	 // 다시 수신인터럽트 활성화 = 재 장전
	 HAL_UART_Receive_IT(&huart1, (uint8_t *)Rx_data_1, 1);

   } //---------------------------------------------------------
  else if(huart -> Instance == USART2)
   {
	 // uart 2 rx int
	 if(Rx_data_2[0] == CR)
	   {
	  	 rx_end_flag_2 = 1;
	     rx_cnt_2 = 0;
	   }
	 else
	  {
	  	Rx_data_2[rx_cnt_2++] = Rx_data_2[0];
	  }

	  // rx text
	  tx_send(Rx_data_2[0], 2); // echo tx

	  // esp8266 tx
	  tx_send(Rx_data_2[0],1);



	 // init flag clr
	 __HAL_UART_CLEAR_PEFLAG(&huart2);

	 // 다시 수신인터럽트 활성화 = 재 장전 = 동기 맞출려면 main에서 해도 됨 = 응용에 따라서
	 HAL_UART_Receive_IT(&huart2, (uint8_t *)Rx_data_2, 1);
   } //----------------------------------------------------------
  else if(huart -> Instance == USART3)
   {
	 // uart 3 rx int == 온습도, 미세먼지, CO2, VCO 센서



	 // 동기 맞출려고 메인에서 온 함
	 // init flag clr
	// __HAL_UART_CLEAR_PEFLAG(&huart3);

	   // 동기 맞출려고 메인에서 온 함
	 // 다시 수신인터럽트 활성화 = 재 장전
	 //HAL_UART_Receive_IT(&huart3, (uint8_t *)Rx_data_3, 1);
   }
}
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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  out_port(M_EN_GPIO_Port,  M_EN_Pin,  1);//stepping motor enable
  out_port(M3_EN_GPIO_Port, M3_EN_Pin, 1);//stepping motor enable

  // \n 필요없이 바로 송신할때 필료 = printf 문 사용 시 = 기본사용
  setvbuf(stdout, NULL, _IONBF, 0);
 // Start_Point(8000);
  // #ifdef my_usart_LIB_en
    // uart rx int 활성화
    HAL_UART_Receive_IT(&huart1, (uint8_t *)Rx_data_1, 2); // uart ch1
    HAL_UART_Receive_IT(&huart2, (uint8_t *)Rx_data_2, 1); // uart ch2
    __HAL_UART_CLEAR_PEFLAG(&huart1);
     Rx_data_1[0] = 0;

    __HAL_UART_CLEAR_PEFLAG(&huart2);
    Rx_data_2[0] = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  //sensor_check();
	  switch(Bluetooth)
	  {
	  case '0':  Start_Point(8000);
	  break;
	  case '1':  ch_1_in(); break;
	  case '2':  ch_2_in(); break;
	  case '3':  ch_3_in(); break;
	  case '4':  ch_4_in(); break;
	  case '5':  ch_5_in(); break;
	  case '6':  ch_6_in(); break;
	  case '7':  ch_1_out(); break;
	  case '8':  ch_2_out(); break;
	  case '9':  ch_3_out(); break;
	  case 'a':  ch_4_out(); break;
	  case 'b':  ch_5_out(); break;
	  case 'c':  ch_6_out(); break;
	  case 'g': break;


	  }
	  delay_ms(1);

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
