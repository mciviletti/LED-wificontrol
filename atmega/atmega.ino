/*
  This code is for the Arduino that will control the LED strip
  It was tested on a Sparkfun Pro Micro 5V 16MHz (AtMega32u4)
*/

#include "led.h"

void setup() {
  Serial1.begin(9600);

  stripSetup();
}

void loop() {
  if(Serial1.available()){
    char command = char(Serial1.read());
    delay(20);  //Small delay so the rest of the command is received
    switch(command) {
      case 'H': //Receives all 3 RGB values at once
        cor.R = Serial1.read();
        cor.G = Serial1.read();
        cor.B = Serial1.read();
        set = true;
        break;
      case 'R': //Receives R value (0 - 255)
        cor.R = Serial1.read();
        set = true;
        break;
      case 'G': //Receives G value (0 - 255)
        cor.G = Serial1.read();
        set = true;
        break;
      case 'B': //Receives B value (0 - 255)
        cor.B = Serial1.read();
        set = true;
        break;
      case 'L': //Receives Brightness value (0 - 255, limited by the ESP)
        setBrightness(Serial1.read());
        break;
      case 'X': //Receives command to do (0xFF) or stop (0x01) rainbow animation
        if(Serial1.read() == 0xFF) {
          doRainbow = true;
        }
        else {
          doRainbow = false;
          set = true;
        }
        break;
      case 'P': //Receives command to do (0xFF) or stop (0x01) pulse animation
        if(Serial1.read() == 0xFF) {
          doPulse = true;
        }
        else {
          doPulse = false;
          set = true;
        }
        break;
    }
  }
  stripHandler();
}
