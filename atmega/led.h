#ifndef LED_H
#define LED_H

#define MAX_LEDS 300  //Set size of used LED strip
#define LED_PIN 9     //Arduino pin connected to the D0 input of LED strip

#define DEFAULT_BRIGHTNESS 50 //Default brightness value, somewhere between 0 - 255. Ideally the same as in led.h on the ESP folder

#define DEFAULT_R     0 //Default R value for the entire strip
#define DEFAULT_G     0 //Default G value for the entire strip
#define DEFAULT_B     0 //Default B value for the entire strip

#define RAINBOW_DELAY 20  //Delay between each rainbow step, increase for slower rainbow animation

#define PULSE_BRIGHTNESS 50 //Max pulse brightness, goes from 0 to this value
#define PULSE_TIME 2000     //Time for half a pulse cycle
#define PULSE_STEPS 50      //How many steps it should go through while increasing/decreasing intensity

#include <Adafruit_NeoPixel.h>

struct RGB {
  uint8_t R;
  uint8_t G;
  uint8_t B;
};

extern RGB cor;

extern bool doPulse, doRainbow, set;

void stripSetup();
void setStripColor();
void setStripColor(uint8_t light);
void setBrightness(uint8_t n);
void stripHandler();
void rainbow();
void pulse();


#endif
