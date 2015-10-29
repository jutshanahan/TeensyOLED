#include "NHD_US2066.h"


const char slave2w = 0x3C;  //3C or 78
unsigned char mode = 1; // 0 = 8-bit parallel 6800 mode; 1 = i2c mode; 2 = SPI mode;
unsigned char tx_packet[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

#define OLED_Address 0x3c
#define OLED_Command_Mode 0x80
#define OLED_Data_Mode 0x40

void command(unsigned char c)
{
  tx_packet[0] = 0x00;
  tx_packet[1] = c;
  send_packet(2);
  
}
void data(unsigned char d)
{
  tx_packet[0] = 0x40;
  tx_packet[1] = d;
  send_packet(2);

}


void sendCommand(unsigned char command)
{
    Wire.beginTransmission(OLED_Address); 	 // **** Start I2C 
    Wire.write(OLED_Command_Mode);     		 // **** Set OLED Command mode
    Wire.write(command);
    Wire.endTransmission();                 	 // **** End I2C 
      delay(10);
}

void cursPos(uint8_t col, uint8_t row)
{
  //int row_offsets[] = { 0x00, 0x20, 0x40, 0x60 };
  //sendCommand(0x80 | (col + row_offsets[row]));
  //command(0x80 + (col + row_offsets[row]));
  command(0x80 | row*0x20);
}




void oled_text(String string, unsigned char row)
{
  char i, strlen;
  //cursPos(0,row);
  
  if (row >=0 && row < 4)
  {
     command(0x80 | row*0x20 );
  }
  else
  {
     Serial.println("Error in oled_text(): row out of range");
     return;
  }
  
  strlen = string.length();
  if (strlen >20) { strlen=20; }
  
  delay(2);
  for(i=0;i<strlen;i++){
    data(string[i]);
  }
  
  for(i=strlen;i<20;i++){    // pad with blank characters
    data(' ');
  }
  
  //delay(2);
}

void send_packet(unsigned char x)
{
  unsigned char ix;
  
  Wire.beginTransmission(slave2w);
  for(ix=0;ix<x;ix++)
  {
    Wire.write(tx_packet[ix]);
  }
  Wire.endTransmission();
}

void init_oled()
{
  //pinMode(ASCL, OUTPUT);      //set Arduino I2C lines as outputs
//  pinMode(ASDA, OUTPUT);      //
//  digitalWrite(ASCL, LOW);    //
//  digitalWrite(ASDA, LOW);    //

  digitalWrite(RES, HIGH);
  delay(10);
  Wire.begin();
  delay(10);

    command(0x2A);  //function set (extended command set)
	command(0x71);  //function selection A, disable internal Vdd regualtor
	data(0x00);
	command(0x28);  //function set (fundamental command set)
	command(0x08);  //display off, cursor off, blink off
	command(0x2A);  //function set (extended command set)
	command(0x79);  //OLED command set enabled
	command(0xD5);  //set display clock divide ratio/oscillator frequency
	command(0x70);  //set display clock divide ratio/oscillator frequency
	command(0x78);  //OLED command set disabled
	command(0x09);  //extended function set (4-lines)
    command(0x06);  //COM SEG direction
	command(0x72);  //function selection B, disable internal Vdd regualtor
	data(0x00);     //ROM CGRAM selection
	command(0x2A);  //function set (extended command set)
	command(0x79);  //OLED command set enabled
	command(0xDA);  //set SEG pins hardware configuration
	command(0x10);  //set SEG pins ... NOTE: When using NHD-0216AW-XB3 or NHD_0216MW_XB3 change to (0x00)
	command(0xDC);  //function selection C
	command(0x00);  //function selection C
	command(0x81);  //set contrast control
	command(0x7F);  //set contrast control
	command(0xD9);  //set phase length
	command(0xF1);  //set phase length
	command(0xDB);  //set VCOMH deselect level
	command(0x40);  //set VCOMH deselect level
	command(0x78);  //OLED command set disabled
	command(0x28);  //function set (fundamental command set)
	command(0x01);  //clear display
	command(0x80);  //set DDRAM address to 0x00
	command(0x0C);  //display ON
  delay(100);
  //Wire.begin();
  //delay(10);
}
