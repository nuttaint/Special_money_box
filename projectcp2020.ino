#include <HCMAX7219.h>    
#include "SPI.h"
#define LOAD 10             /* Set the LOAD (CS) GPIO12=D6 */
HCMAX7219 HCMAX7219(LOAD);
const int pinIr025b = A0;     /* กำหนดขาให้เซ็นเซอร์เหรียญ 25 สตางค์ */
const int pinIr050b = A1;     /* กำหนดขาให้เซ็นเซอร์เหรียญ 50 สตางค์ */
const int pinIr1b = A2;       /* กำหนดขาให้เซ็นเซอร์เหรียญ 1 บาท */
const int pinIr2b = A3;       /* กำหนดขาให้เซ็นเซอร์เหรียญ 2 บาท */
const int pinIr5b = A4;       /* กำหนดขาให้เซ็นเซอร์เหรียญ 5 บาท */
const int pinIr10b = A5;      /* กำหนดขาให้เซ็นเซอร์เหรียญ 10 บาท */

int IRvalue025b = 0;          /* ตั้งค่าตัวแปรเก็บระยะห่างเซ็นเซอร์เหรียญ 25 สตางค์ */
int totalcoin025 = 0;         /* ตั้งค่าตัวแปรเก็บจำนวนเหรียญ 25 สตางค์ */

int IRvalue050b = 0;          /* ตั้งค่าตัวแปรเก็บระยะห่างเซ็นเซอร์เหรียญ 50 สตางค์ */
int totalcoin050 = 0;         /* ตั้งค่าตัวแปรเก็บจำนวนเหรียญ 50 สตางค์ */

int IRvalue1b = 0;            /* ตั้งค่าตัวแปรเก็บระยะห่างเซ็นเซอร์เหรียญ 1 บาท */
int totalcoin1 = 0;           /* ตั้งค่าตัวแปรเก็บจำนวนเหรียญ 1 บาท */

int IRvalue2b = 0;            /* ตั้งค่าตัวแปรเก็บระยะห่างเซ็นเซอร์เหรียญ 2 บาท */
int totalcoin2 = 0;           /* ตั้งค่าตัวแปรเก็บจำนวนเหรียญ 2 บาท */

int IRvalue5b = 0;            /* ตั้งค่าตัวแปรเก็บระยะห่างเซ็นเซอร์เหรียญ 5 บาท */
int totalcoin5 = 0;           /* ตั้งค่าตัวแปรเก็บจำนวนเหรียญ 5 บาท */

int IRvalue10b = 0;           /* ตั้งค่าตัวแปรเก็บระยะห่างเซ็นเซอร์เหรียญ 10 บาท */
int totalcoin10 = 0;          /* ตั้งค่าตัวแปรเก็บจำนวนเหรียญ 10 บาท */

float totalAll = 0;           /* รวมค่าของจำนวนเหรียญทุกประเภท */


void setup()
{
  HCMAX7219.Intensity(3, 0);         /* ปรับระดับความเข้มแสง */
  Serial.begin(9600); 
  pinMode(pinIr025b,INPUT); 
  pinMode(pinIr050b,INPUT);
  pinMode(pinIr1b,INPUT);
  pinMode(pinIr2b,INPUT);
  pinMode(pinIr5b,INPUT);
  pinMode(pinIr10b,INPUT);
}


void loop()
{
  HCMAX7219.Clear();                   /* ทำการเคลียร์หน้าจอ output */
  if (totalAll < 0)
    totalAll *= -1;
  HCMAX7219.print7Seg(totalAll, 2, 8); /*แสดงผลจำนวนเงินออกทางหน้าจอ */
  HCMAX7219.Refresh(); 
   /*ทำการอ่านค่าจากขาที่อินพุทเข้ามา*/
  IRvalue025b = analogRead(pinIr025b);
  IRvalue050b = analogRead(pinIr050b);
  IRvalue1b = analogRead(pinIr1b);
  IRvalue2b = analogRead(pinIr2b);
  IRvalue5b = analogRead(pinIr5b);
  IRvalue10b = analogRead(pinIr10b);
  
  /*ตั้งเงื่อนไขให้เซ็นเซอร์ทำงานโดยที่ 60 คือระยะห่างเซ็นเซอร์กับตัววัตถุ */
  if (IRvalue025b < 60) {
    totalcoin025++;
    Serial.println(totalAll);
    delay(250);
  }
  if (IRvalue050b < 60) {
    totalcoin050++;
    Serial.println(totalAll);
    delay(250);
  }
  
  if (IRvalue1b < 60) {
    totalcoin1++;
    Serial.println(totalAll);
    delay(250);
  }
  
  if (IRvalue2b < 60) {
    totalcoin2++;
    Serial.println(totalAll);
    delay(250);
  }
  
  if (IRvalue5b < 60) {
    totalcoin5++;
    Serial.println(totalAll);
    delay(250);
  }
  
  if (IRvalue10b < 60) {
    totalcoin10++;
    Serial.println(totalAll);
    delay(250);
  }

  
  totalAll = (totalcoin025 * 0.25) + (totalcoin050 * 0.50) + (totalcoin1 * 1) + (totalcoin2 * 2) + (totalcoin5 * 5) + (totalcoin10 * 10);
  totalAll = totalAll * 100;
}
