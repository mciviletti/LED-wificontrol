#ifndef LED_H
#define LED_H

#define DEFAULT_BRIGHTNESS 50 //Default brightness value on the HTML page (must be between 0 and MAX_BRIGHTNESS)
#define MAX_BRIGHTNESS 100    //Max brightness value on the slider (must be between 1 and 255)

#define DEFAULT_R     0 //Default R value on the HTML page
#define DEFAULT_G     0 //Default G value on the HTML page
#define DEFAULT_B     0 //Default B value on the HTML page

struct RGB {
  uint8_t R;
  uint8_t G;
  uint8_t B;
};

#endif
