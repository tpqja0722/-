

// My Gpio lib
// 송 명 규
// 010-2402-4398
// End Ver = V1.0
// Ver1.0 = 2018, 07, 09
// Ver2.0 = 2019, 11, 08 //


#ifndef __my_gpio_lib__
#define __my_gpio_lib__

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"

// 1. GPIO OUTPUT LIB
#define ON    1
#define OFF   0
#define _ON   0
#define _OFF  1

#define Low  GPIO_PIN_RESET
#define Hi   GPIO_PIN_SET
#define out_port(port, pin, out_data_bits) HAL_GPIO_WritePin(port, pin, out_data_bits)
#define out_tg(port, pin)  HAL_GPIO_TogglePin(port, pin)

//2. GPIO INPUT LIB
#define in_port(port, pin) HAL_GPIO_ReadPin(port, pin)

// 3. all_pin 제어하는게 있음 = 차후 보강할 예정

//4. SyStem delay LIB = 워링은 나지만 정상 동작함
#define delay_ms(val)  HAL_Delay(val)

//2019, 11, 08 추가
void byte_out_L(GPIO_TypeDef *GPIOx, uint16_t out_data, uint8_t mask) // uint32_t = org = data sheet 상
{
  // Low 8bit out = default
  if(mask == 1) GPIOx -> ODR = (out_data & 0xffff);
  else GPIOx -> ODR = (out_data & 0x00ff);
}

void byte_out_H(GPIO_TypeDef *GPIOx, uint16_t out_data, uint8_t mask) // uint32_t = org = data sheet 상
{
   // High 8bit out
	out_data <<= 8;
	if(mask == 1) GPIOx -> ODR = (out_data & 0xffff) ;
	else GPIOx -> ODR = ((out_data & 0xff00) | 0xff);
}

void word_out(GPIO_TypeDef *GPIOx, uint16_t out_data)
{
   // 16 bit out
	GPIOx -> ODR = out_data;
}

uint16_t byte_rd_L(GPIO_TypeDef *GPIOx)
{
  // Low 8 bit input
  uint16_t buf;
  buf =  GPIOx -> IDR;
  return (buf & 0x00ff);
}

uint16_t byte_rd_H(GPIO_TypeDef *GPIOx)
{
  // high 8bit input
  uint16_t buf;

  buf =  GPIOx -> IDR;
  return (buf & 0xff00);
}

uint16_t word_rd(GPIO_TypeDef *GPIOx)
{
  // 16bit input
  return  GPIOx -> IDR;
}



// 1. gpio output LIB test sample code
/*
void led_demo(void)
{
   out_port(GPIOA, R_LED_OUT_Pin | B_LED_OUT_Pin, 1);
   delay_ms(500); //3. System delay LIB test
   out_port(GPIOA, R_LED_OUT_Pin | B_LED_OUT_Pin, 0); // led 2
   delay_ms(500);

   out_tg(GPIOA, RGB_B_LED_OUT_Pin);
   delay_ms(500);
   out_port(R_LED_OUT_GPIO_Port, R_LED_OUT_Pin, 1);
   delay_ms(500);
   out_tg(GPIOA, R_LED_OUT_Pin | B_LED_OUT_Pin | RGB_B_LED_OUT_Pin );
   delay_ms(500);
   out_tg(BZ_OUT_GPIO_Port, BZ_OUT_Pin);

   out_port(RGB_R_LED_OUT_GPIO_Port, RGB_R_LED_OUT_Pin, Hi);
   HAL_Delay(200);
   out_port(RGB_R_LED_OUT_GPIO_Port, RGB_R_LED_OUT_Pin, Low);

   out_port(RBG_G_LED_OUT_GPIO_Port, RBG_G_LED_OUT_Pin, Hi);
   HAL_Delay(200);
   out_port(RBG_G_LED_OUT_GPIO_Port, RBG_G_LED_OUT_Pin, Low);

   out_port(RGB_B_LED_OUT_GPIO_Port, RGB_B_LED_OUT_Pin, 1);
   HAL_Delay(200);
   out_port(RGB_B_LED_OUT_GPIO_Port, RGB_B_LED_OUT_Pin, 0);

   HAL_Delay(200);
   out_port(RGB_R_LED_OUT_GPIO_Port, RGB_R_LED_OUT_Pin, Hi);
   out_port(RBG_G_LED_OUT_GPIO_Port, RBG_G_LED_OUT_Pin, GPIO_PIN_SET);
   out_port(RGB_B_LED_OUT_GPIO_Port, RGB_B_LED_OUT_Pin, 1);
   HAL_Delay(200);
   out_port(RGB_R_LED_OUT_GPIO_Port, RGB_R_LED_OUT_Pin, 0);
   out_port(RBG_G_LED_OUT_GPIO_Port,  RBG_G_LED_OUT_Pin, GPIO_PIN_RESET);
   out_port(RGB_B_LED_OUT_GPIO_Port, RGB_B_LED_OUT_Pin, Low);
   HAL_Delay(200);
   out_tg(BZ_OUT_GPIO_Port, BZ_OUT_Pin);
   HAL_Delay(200);
}
*/


//2. gpio input test LIB sample code
/*
void key_in(void)
{
	if(in_port(SW1_IN_GPIO_Port, SW1_IN_Pin) == 0)
	    {
		   out_port(GPIOA, LED1_Pin | LED2_RED_Led_Pin, 1);
	    }
	   else out_port(GPIOA, LED1_Pin | LED2_RED_Led_Pin, 0);

	   if(in_port(SW2_IN_GPIO_Port, SW2_IN_Pin) == 0)
	      {
		    out_port(RGB_R_Led_GPIO_Port, RGB_R_Led_Pin, 0);
		    out_port(RGB_G_Led_GPIO_Port, RGB_G_Led_Pin, GPIO_PIN_RESET);
		    out_port(RGB_B_Led_GPIO_Port, RGB_B_Led_Pin, Low);
	  	    led_demo();
	      }
	   else
	    {
		  out_port(RGB_R_Led_GPIO_Port, RGB_R_Led_Pin, Hi);
		  out_port(RGB_G_Led_GPIO_Port, RGB_G_Led_Pin, GPIO_PIN_SET);
		  out_port(RGB_B_Led_GPIO_Port, RGB_B_Led_Pin, 1);
	    }
}
*/


#endif
