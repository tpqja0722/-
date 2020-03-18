

// My Uart lib
// �� �� ��
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

#include "stdio.h"  // printf, sprintf ���� �߰�
#include <stdarg.h>
#include <string.h>

void vprint(const char *fmt, va_list argp);
void my_printf(const char *fmt, ...); // custom printf() function
void tx_send(uint8_t tx_data, uint8_t ch);

 // org LIB ����
HAL_StatusTypeDef RcvStat;
uint8_t usart_ch = 1;  // Nrcleo default usart ch = 2
uint8_t Rx_data_1[10];  // uart 1 rx_buf
uint8_t Rx_data_2[20];  // uart 2 rx_buf
uint8_t Rx_data_3[30];  // uart 3 rx_buf

uint8_t rx_cnt_1 = 0;    // uart 1 ���� ������ byte ī����
uint8_t rx_cnt_2 = 0;    // uart 2 ���� ������ byte ī����
uint8_t rx_cnt_3 = 0;    // uart 3 ���� ������ byte ī����

uint8_t rx_end_flag_1 = 0; // ���ſϷ� ���� �Ǵ� flag
uint8_t rx_end_flag_2 = 0; // ���ſϷ� ���� �Ǵ� flag
uint8_t rx_end_flag_3 = 0; // ���ſϷ� ���� �Ǵ� flag
#endif

// W5500
uint8_t my_buf[10] = "song\n\r";
uint8_t user[10] = "sg\n\r";


// printf ����ϰ��� �߰�
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
   case 1: // uart 1 = CubeMX���� ����ϰڴٰ� ���� ���ϸ� ���� ��
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
  // uart �� ���ڿ� ���۽�
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
 char *bak = "Home@# �츮��";
 char *cur;



// UART RTX sample code
// main.c �ȿ� �ش�ȭ�� ȣ���ϱ����� �ݵ�� �ڵ��� �� = uart ���ÿ���... 
#define my_usart_LIB_en 1

 // usart rx int �� ���� ���ͷ�Ʈ ���� main �Լ� while�� ������ �ڵ��Ұ� = ���Ÿ�� ���� = ���� ���ͷ�Ʈ Ȱ��ȭ
#ifdef my_usart_LIB_en
 HAL_UART_Receive_IT(&huart2, (uint8_t *)Rx_data, 1); // 1 byte rx int ����

// �ٸ���� ��
//if (HAL_UART_Receive_IT(&huart2, (uint8_t *)Rx_data, 10) != HAL_OK) {
    //       Error_Handler();
   //    }


  if (HAL_UART_Receive_IT(&UartHandle, (uint8_t *)aRxBuffer, RXBUFFERSIZE) != HAL_OK) {
          Error_Handler();
      }


// ���� ���ͷ�Ʈ ��� sample code     
// usart RX INT func = ���� ���ͷ�Ʈ �Լ�
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

  // �ٽ� �������ͷ�Ʈ Ȱ��ȭ = �� ����
  HAL_UART_Receive_IT(&huart2, (uint8_t *)Rx_data, 1);
}
*/

// main �Լ� �ȿ��� ����������� ����üũ sample code
// polong rx chk samplae code
void poling_rx_chk(void)
{
	  RcvStat = HAL_UART_Receive(&huart2, Rx_data_2, 1, 100) ;  // receive data
	  if (RcvStat == HAL_OK)
	  	{
	  	  // receive check
	  	  HAL_UART_Transmit(&huart2, Rx_data_2, 1, 100) ;  // echo tx send received data
	   	  HAL_UART_Transmit(&huart2, Rx_data_2, 10, 100);  // send start data

	      // my_printf("uart OK �۸��= %d,hex = %x, float = %.4f, char = %c, string = %s int16 = %d!@#\n\r",cnt, cnt, rr, k, bak, ss);
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

  // �ٸ��ҽ��ڵ�
  // cur = rcvdata;
  // sprintf(cur,"song\n\r");
   //int len = strlen(cur);
  // HAL_UART_Transmit(&huart2, (uint8_t *)&cur, len,100);
}



#endif

