#include "Wire.h"
#include "Arduino.h"


#define RS   30
#define E    31
#define RES  32
#define CS   33

#define ASDA  20
#define ASCL  21



// R/W signal tied LOW (always write)
// SA0 signal tied LOW

void init_oled();
void send_packet(unsigned char x);
void data(unsigned char d);
void command(unsigned char c);
void oled_text(String string, unsigned char row);
