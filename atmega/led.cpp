#include "LED.h"
#include <Adafruit_NeoPixel.h>

RGB cor;  //Holds current RGB values as a Struct

Adafruit_NeoPixel strip  = Adafruit_NeoPixel(MAX_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);  //Set parameters for current LED strip, default values for WS2812b

bool doPulse, doRainbow, set;

long firstPixelHue;

uint8_t brightness;

void stripSetup() {

  cor.R = DEFAULT_R; cor.G = DEFAULT_G; cor.B = DEFAULT_B;

  strip.begin();
  strip.clear();
  strip.show();
  brightness = DEFAULT_BRIGHTNESS;
  firstPixelHue = 0;
  setStripColor();
  doPulse = false;
  doRainbow = false;
  set = false;
}

void setStripColor(){
  setStripColor(brightness);
}

void setStripColor(uint8_t light){
  uint16_t r, g, b;
  if(strip.getBrightness() != 255) {
    strip.setBrightness(255); //strip.brightness is not used because it destroys the stored RGB values
  }
  r = cor.R*light/255;
  g = cor.G*light/255;
  b = cor.B*light/255;
  for(uint16_t n = 0; n < strip.numPixels(); n++){
    strip.setPixelColor(n, r, g, b);
  }
  strip.show();
}

void setBrightness(uint8_t n) {
  brightness = n;
  setStripColor();
}

void stripHandler() {
  if(doRainbow) {
    if(strip.getBrightness() != brightness) {
      strip.setBrightness(brightness);
    }
    rainbow();
  }
  else if(doPulse) {
    pulse();
  }
  else if (set) {
    setStripColor();
  }
  set = false;
  delay(1);
}

void rainbow() {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    // Offset pixel hue by an amount to make one full revolution of the
    // color wheel (range of 65536) along the length of the strip
    // (strip.numPixels() steps):
    int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
    // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
    // optionally add saturation and value (brightness) (each 0 to 255).
    // Here we're using just the single-argument hue variant. The result
    // is passed through strip.gamma32() to provide 'truer' colors
    // before assigning to each pixel:
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
  }
  strip.show(); // Update strip with new contents
  firstPixelHue += 256;
  if(firstPixelHue >= 5*65536) {
    firstPixelHue = 0;
  }
  delay(RAINBOW_DELAY);  // Pause for a moment
}

void pulse() {
  uint8_t intensity;
  for(int i = PULSE_STEPS; i > 0; i--) {
    intensity = i*PULSE_BRIGHTNESS/PULSE_STEPS;
    setStripColor(intensity);
    delay(PULSE_TIME/(2*(PULSE_STEPS)));
  }
  for(int i = 0; i < PULSE_STEPS; i++) {
    intensity = i*PULSE_BRIGHTNESS/PULSE_STEPS;
    setStripColor(intensity);
    delay(PULSE_TIME/(2*(PULSE_STEPS)));
  }
}
