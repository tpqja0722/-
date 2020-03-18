/*
 * FND_LIB.h
 *
 *  Created on: 2019. 12. 6.
 *      Author: user
 */

#ifndef FND_LIB_H_
#define FND_LIB_H_

#include "main.h"
// fnd font
const uint8_t fnd_font[] =
{
   // 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   H,   L,   E,   o,   P,  F,
   0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x6f,0x76,0x38,0x79,0x5c,0x73,0x71,
   // C,    d,    A,    u,    T,    r,   b,  blk
   0x39, 0x5e, 0x77, 0x1c, 0x44, 0x50, 0x7c, 0x00
};

// fnd maseg display = 영문font
#define O   0x0d   //o display
#define F   0x0f    // F display
#define H   0x0a    // H   "
#define L   0x0b    // L   "
#define E   0x0c    // E   "
#define P   0x0e    // P   "
#define C   0x10    // C   "
#define D   0x11    // d   "
#define A   0x12    // A   "
#define U   0x13    // u   "
#define T   0x14    // t   "
#define R   0x15    // r   "
#define b   0x16    // b   "
#define BLK 0x17   // fnd blk display 0x00

// fnd c-a
#define fnd_on  1
#define fnd_off 0

// fnd c-c
#define fnd_on_  0
#define fnd_off_ 1

// h/w pin define = 프로젝트마다 수정 요
// fnd com control
#define x1000 X_1000_Pin // porta.4
#define x100  X_100_Pin
#define x10   X_10_Pin
#define x1    X_1_Pin

#define fnd_out(val) byte_out_L(GPIOB, val, 0)  // 프로젝트마다 수정 요

// 변수선언
uint8_t scan = 0;

// fnd display my lib

// 카운터 시 나 기본fnd display 함수
// + 콤 = CA+
void fnd_dis_ca(uint16_t fnd_d)
{
  scan++;
  if(scan > 4) scan = 1;

  switch(scan)
   {
     // c-a
     case 1: // x1000
    	     out_port(GPIOA, x1, fnd_off);
             fnd_out(~fnd_font[fnd_d/1000]);
             out_port(GPIOA, x1000, fnd_on);
      break;

     case 2: // x100
    	     out_port(GPIOA, x1000, fnd_off);
             fnd_out(~fnd_font[fnd_d%1000/100]);
             out_port(GPIOA, x100, fnd_on);
      break;

     case 3: // x10
    	     out_port(GPIOA, x100, fnd_off);
             fnd_out(~fnd_font[fnd_d%100/10]);
             out_port(GPIOA, x10, fnd_on);
      break;

     case 4: // x1
    	     out_port(GPIOA, x10, fnd_off);
             fnd_out(~fnd_font[fnd_d%10]);
             out_port(GPIOA, x1, fnd_on);
      break;
   }
}

// - 콤 = CK-
void fnd_dis_ck(uint16_t fnd_d)
{
  scan++;
  if(scan > 4) scan = 1;

  switch(scan)
   {
     // c-c
     case 1: // x1000
    	     out_port(GPIOA, x1, fnd_off_);
             fnd_out(fnd_font[fnd_d/1000]);
             out_port(GPIOA, x1000, fnd_on_);
      break;

     case 2: // x100
    	     out_port(GPIOA, x1000, fnd_off_);
             fnd_out(fnd_font[fnd_d%1000/100]);
             out_port(GPIOA, x100, fnd_on_);
      break;

     case 3: // x10
    	     out_port(GPIOA, x100, fnd_off_);
             fnd_out(fnd_font[fnd_d%100/10]);
             out_port(GPIOA, x10, fnd_on_);
      break;

     case 4: // x1
    	     out_port(GPIOA, x10, fnd_off_);
             fnd_out(fnd_font[fnd_d % 10]);
             out_port(GPIOA, x1, fnd_on_);
      break;
   }
}



/*
// 시계할때 사용
void fnd_dis_2(int fnd_d, int fnd_da)
{
  scan++;
  if(scan > 8) scan = 1;

  switch(scan)
   {
     // c-c
     case 1: // x1000
             x1_ = off_;
             fnd_out(fnd_font[fnd_d/1000]);
             x1000 = on_;
      break;

     case 2: // x100
             x1000 = off_;
             fnd_out(fnd_font[fnd_d%1000/100]);
             x100 = on_;
      break;

     case 3: // x10
             x100 = off_;
             fnd_out(fnd_font[fnd_d%100/10]);
             x10 = on_;
      break;

     case 4: // x1
             x10 = off_;
            if(tg_flag == 1) fnd_out(fnd_font[O] | 0x80);
            else fnd_out(fnd_font[O] & 0x7f);
             x1 = on_;
      break;
   }
}
*/


#endif /* FND_LIB_H_ */
