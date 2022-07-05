/*
 * time.c
 *
 * Created: 2022-04-25 오후 1:43:01
 * Author : kim_j
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <time.h>

// 7-segment FND를 위한 숫자들
#define ZERO 0x7f  //01111111
#define ONE 0x06  //00000110
#define TWO 0x5b  //01011011
#define THREE 0x4f  //01001111
#define FOUR 0x66  //01100110
#define FIVE 0x6d //01101101
#define SIX 0x7d //01111101
#define SEVEN 0x07 //00000111
#define EIGHT 0x7f //01111111
#define NINE 0x6f //01101111


// 스텝 모터 각속도 조절을 위한 배열
const unsigned char data[8] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0c, 0x08, 0x09};
   
volatile unsigned char _state;


int main(void)
{
   DDRF = 0xff;  // 핀 출력
   DDRE = 0xff;
   PORTF = 0x0f;
   
   DDRG = 0x00;  // 핀 입력
   DDRC = 0x00;
   PORTE = ZERO;
   int count = 0;
   while(1) { 
      
   
      if (PING & 0x01){  // 동작감지센서 감지시
         count++;  // 작동시마다 count변수에 1씩 더함
         switch (count) {
            case 1:
               PORTE = ONE;
               break;
            case 2:
               PORTE = TWO;
               break;
            case 3:
               PORTE = THREE;
               break;
            case 4:
               PORTE = FOUR;
               break;
            case 5:
               PORTE = FIVE;
               break;
            case 6:  // 5번 작동시 10초간 휴식
               count = 0;
               PORTE = ZERO;
               _delay_ms(1000);
               PORTE = ONE;
               _delay_ms(1000);
               PORTE = TWO;
               _delay_ms(1000);
               PORTE = THREE;
               _delay_ms(1000);
               PORTE = FOUR;
               _delay_ms(1000);
               PORTE = FIVE;
               _delay_ms(1000);
               PORTE = SIX;
               _delay_ms(1000);
               PORTE = SEVEN;
               _delay_ms(1000);
               PORTE = EIGHT;
               _delay_ms(1000);
               PORTE = NINE;
               _delay_ms(1000);
               PORTE = ZERO;
               break;
         }
         // 부저 알림
         for(int i = 0; i < 10; i++){
            PORTF = 0x10;
            _delay_ms(10);
         }
         int i = 0;
         for(int j = 0; j < 10000; j++){
            PORTF = data[i];
            _delay_us(800);
            i++;
            if(i == 8){
               i = 0;
            }
            if ((PINC % 2 == 1)) {  // 소리감지센서 감지시 반대로 회전
               for(int i = 0; i < 10; i++){  // 두번 울림
                  PORTF = 0x10;
                  _delay_ms(10);
               }
               _delay_ms(300);
               for(int i = 0; i < 10; i++){
               PORTF = 0x10;
               _delay_ms(10);
            }
               for(int k = 0; k < 5000; k++){
                  PORTF = data[i];
                  _delay_us(900);
                  i--;
                  if(i == -1){
                     i = 7;
                  }
                  
               }
               break;
            }
         }
      }
   } 
}
