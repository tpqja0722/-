

// My Uart lib
// 송 명 규
// 010-2402-4398
// End Ver = V2.0
// Ver1.0 = 2018, 07, 09
// Ver2.0 = 2019, 05, 19


#ifndef __my_uart_lib__
#define __my_uart_lib__


#ifdef my_usart_LIB_en

#define CR	0x0D    //13
#define LF	0x0A    //10
#define Uart_Ch_1	1
#define Uart_Ch_2	2
#define Uart_Ch_3	3

#include "stdio.h"  // printf, sprintf 사용시 추가
#include <stdarg.h>
#include <string.h>

void vprint(const char *fmt, va_list argp);
void my_printf(const char *fmt, ...); // custom printf() function
void tx_send(uint8_t tx_data, uint8_t ch);

 // org LIB 변수
HAL_StatusTypeDef RcvStat;
uint8_t usart_ch = 1;  // Nrcleo default usart ch = 2
uint8_t Rx_data_1[10];  // uart 1 rx_buf
uint8_t Rx_data_2[20];  // uart 2 rx_buf
uint8_t Rx_data_3[30];  // uart 3 rx_buf

uint8_t rx_cnt_1 = 0;    // uart 1 수신 데이터 byte 카운터
uint8_t rx_cnt_2 = 0;    // uart 2 수신 데이터 byte 카운터
uint8_t rx_cnt_3 = 0;    // uart 3 수신 데이터 byte 카운터

uint8_t rx_end_flag_1 = 0; // 수신완료 여부 판단 flag
uint8_t rx_end_flag_2 = 0; // 수신완료 여부 판단 flag
uint8_t rx_end_flag_3 = 0; // 수신완료 여부 판단 flag
#endif

// W5500
uint8_t my_buf[10] = "song\n\r";
uint8_t user[10] = "sg\n\r";


// printf 사용하고자 추가
int fputc(int ch, FILE *f)
 {
     uint8_t temp[1]={ch};
     HAL_UART_Transmit(&huart2, temp, 1, 2);
   return(ch);
 }


// my usart LIB
void tx_send(uint8_t tx_data, uint8_t ch)
{
 switch(ch)
  {
   case 1: // uart 1 = CubeMX에서 사용하겠다고 정의 안하면 에러 남
          //HAL_UART_Transmit(&huart1, (uint8_t *)&tx_data, 1,10);
      break;

   case 2: // uart 2
             HAL_UART_Transmit(&huart2, (uint8_t *)&tx_data, 1, 10);
         break;

   case 3: // uart 3
             //HAL_UART_Transmit(&huart3, (uint8_t *)&tx_data, 1,10);
         break;
  }
}

void tx(uint8_t *tx_d, uint8_t ch)
{
  // uart 로 문자열 전송시
  while(*tx_d != '\0')
  {
    tx_send(*tx_d, ch);
    tx_d++;
  }
}


void vprint(const char *fmt, va_list argp)
{
    char string[200];
    if(0 < vsprintf(string,fmt,argp)) // build string
    {
        if(usart_ch == 2) HAL_UART_Transmit(&huart2, (uint8_t*)string, strlen(string), 0xffffff); // send message via UART
        //else if(usart_ch == 3) HAL_UART_Transmit(&huart3, (uint8_t*)string, strlen(string), 0xffffff); // send message via UART
        //else if (usart_ch == 1) HAL_UART_Transmit(&huart1, (uint8_t*)string, strlen(string), 0xffffff); // send message via UART
    }
}

void my_printf(const char *fmt, ...) // custom printf() function
{
    va_list argp;
    va_start(argp, fmt);
    vprint(fmt, argp);
    va_end(argp);
}



//=============================================================
/*
// uart test
 uint8_t my_buf[10] = "song\n\r";
 uint8_t user[10] = "sg\n\r";
 uint8_t pin_str_flag;

 uint8_t cnt= 255;

 char k = 'Y';
 float rr = 3.14;
 int ss= 7965539;  //uint16_t ss = 65535;
 char *bak = "Home@# 우리집";
 char *cur;



// UART RTX sample code
// main.c 안에 해더화일 호출하기전에 반드시 코딩할 것 = uart 사용시에만... 
#define my_usart_LIB_en 1

 // usart rx int 즉 수신 인터럽트 사용시 main 함수 while문 위에다 코딩할것 = 수신모드 시작 = 수신 인터럽트 활성화
#ifdef my_usart_LIB_en
 HAL_UART_Receive_IT(&huart2, (uint8_t *)Rx_data, 1); // 1 byte rx int 선언

// 다른사용 예
//if (HAL_UART_Receive_IT(&huart2, (uint8_t *)Rx_data, 10) != HAL_OK) {
    //       Error_Handler();
   //    }


  if (HAL_UART_Receive_IT(&UartHandle, (uint8_t *)aRxBuffer, RXBUFFERSIZE) != HAL_OK) {
          Error_Handler();
      }


// 수신 인터럽트 사용 sample code     
// usart RX INT func = 수신 인터럽트 함수
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
 if(huart -> Instance == USART2)
  {
	  HAL_UART_Transmit(&huart2, bufftx, 10, 100);

    if(Rx_data[0] == '\r')
     {
       rx_cnt = 0;
       rx_end_flag = 1;
       Rx_data[0] = 0;
     }
    else
    {
      rx_buf[rx_cnt++] = Rx_data[0];

      tx_send('K',2);
    }
  }

  // 다시 수신인터럽트 활성화 = 재 장전
  HAL_UART_Receive_IT(&huart2, (uint8_t *)Rx_data, 1);
}
*/

// main 함수 안에서 폴링방식으로 수신체크 sample code
// polong rx chk samplae code
void poling_rx_chk(void)
{
	  RcvStat = HAL_UART_Receive(&huart2, Rx_data_2, 1, 100) ;  // receive data
	  if (RcvStat == HAL_OK)
	  	{
	  	  // receive check
	  	  HAL_UART_Transmit(&huart2, Rx_data_2, 1, 100) ;  // echo tx send received data
	   	  HAL_UART_Transmit(&huart2, Rx_data_2, 10, 100);  // send start data

	      // my_printf("uart OK 송명규= %d,hex = %x, float = %.4f, char = %c, string = %s int16 = %d!@#\n\r",cnt, cnt, rr, k, bak, ss);
          //  tx_send('W',2);
          //  tx("uart SMG!\n\r",2);

          //  tx_send(cnt/100 + 0x30,2);
          //  tx_send(cnt%100/10 + '0',2);
          //  tx_send(cnt%10 + 0x30,2);

	   	  // uart rx data test
	   	  // if(UsartData[0] == 'a')  //out_tg(GPIOA, LED1_Pin);
	   	  // else if(UsartData[0] == 'b') //out_tg(GPIOA, GPIO_PIN_6);
	  	}
}

void uart_poling_rtx_test(void)
{
// uart poling rtx test
   poling_rx_chk();
  // tx_send('K',2);
}   
 
void uart_int_test(void)
{  
 // 4. uart rx int test
	if(rx_end_flag_1 == 1)
	 {
	//   tx_send(rx_buf[0],2);
	//   tx_send(rx_buf[1],2);
	//   tx_send(rx_buf[2],2);

	   rx_end_flag_1 = 0;
	 }
}

void sprintf_test(void)
{    
  //sprintf test
	//printf(rcvdata,"%4d",cnt);
	//HAL_UART_Transmit(&huart3, (uint8_t *)&rcvdata, 10,100);

  // 다른소스코드
  // cur = rcvdata;
  // sprintf(cur,"song\n\r");
   //int len = strlen(cur);
  // HAL_UART_Transmit(&huart2, (uint8_t *)&cur, len,100);
}



#endif

