//---------------------------------------------------------
/*

Example code for NewHaven NHD-0420CW OLED character display using US2066 controller and I2C connection.
http://www.newhavendisplay.com/oled-slim-character-oleds-c-119_825.html
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
  
  unsigned int a1,a2,a3,d0,d1;
  
  while(1){
    

    a1=touchRead(A1);
    a2=touchRead(A2);
    a3=touchRead(A3);
    d0=touchRead(0);
    d1=touchRead(1);
    
    //a1=a2=a3=d0=d1=1234;
  
    

    sprintf(line1,"d0=%d  d1=%d",d0,d1);  oled_text(line1,0);
    sprintf(line1,"A1=%d",a1);        oled_text(line1,1);
    sprintf(line1,"A2=%d",a2);        oled_text(line1,2);
    sprintf(line1,"A3=%d",a3);        oled_text(line1,3);

    
 
    Serial.println("main");
    delay(100);

    
  }


}
