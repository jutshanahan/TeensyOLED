//---------------------------------------------------------
/*

NHD_0420CW_AX3.ino

Program for writing to Newhaven Display Slim OLEDs based on US2066 controller.

Pick one up today in the Newhaven Display shop!
------> http://www.newhavendisplay.com/oled-slim-character-oleds-c-119_825.html

This code is written for the Arduino Mega.

Copyright (c) 2015 - Newhaven Display International, Inc.

Newhaven Display invests time and resources providing this open source code,
please support Newhaven Display by purchasing products from Newhaven Display!

*/
//---------------------------------------------------------


#include <Arduino.h>
#include <Wire.h>
#include <avr\io.h>

#include "NHD_US2066.h"


void setup()
{
  init_oled();
  Serial.begin(9600);
  Serial.println("init");
  
}

void loop() 
{  
  
  char line1[20];
  
  unsigned int a0,a1,a2,a3;
  
  while(1){
    
    a0=touchRead(A0);
    a1=touchRead(A1);
    a2=touchRead(A2);
    a3=touchRead(A3);
  
    sprintf(line1,"A0=%d",a0);
    oled_text(line1,1);
    sprintf(line1,"A1=%d",a1);
    oled_text(line1,2);
    sprintf(line1,"A2=%d",a2);
    oled_text(line1,3);
    sprintf(line1,"A3=%d",a3);
    oled_text(line1,4);
    
    /*
    oled_text("mah fuckas",2);
    oled_text("jroc all up in this mah",3);
    oled_text("12345abcde12345vwxyz",4);
    */
    Serial.println("main");
    delay(100);

    
  }


}
