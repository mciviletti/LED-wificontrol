# LED-wificontrol
Control of a WS2812 LED via wi-fi using ESP32 and Arduino



## Table of Contents

* [About the Project](#about-the-project)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
* [Comments](#comments)
* [Contributing](#contributing)



## About The Project

This is a small project I built for my own home and decided to share with everyone. I used a ESP32 dev board to host a webserver so that I could send it commands with my phone/computer and control a WS2812b LED strip. I used Adafruit's NeoPixel library, but for some reason it does not work well with the ESP32, so for this first version I added a Sparkfun Pro Micro 5v 16Mhz board to receive Serial commands from the ESP and control the LED strip. In the future, I will update the code so that only the ESP is required.

The whole project was developed on the Arduino IDE for practical reasons.

The basis of the ESP32 server was developed using <a href="https://randomnerdtutorials.com/esp32-web-server-spiffs-spi-flash-file-system/"> this tutorial </a>.

The ESP32 hosts a webserver - you can access it and use your client to send POST commands to the server to control the LED strip.

## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

This project requires an Arduino board (ideally using ATMega32u4 or ATMega328), an ESP32 dev board, an addressable WS2812b LED strip and a 5V power supply.

* Arduino IDE

<a href = "https://www.arduino.cc/en/Main/software">Download and install the Arduino IDE. </a>

* ESP32 addon

<a href = "https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/"> Follow these steps </a> to install the ESP32 addon for the Arduino IDE.

* SPIFFS

<a href = "https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/"> Follow these steps </a> to install SPIFFS, which allow the upload of the HTML, CSS and JavaScript files for the webserver.

* Libraries

Download the <a href="https://github.com/me-no-dev/AsyncTCP"> ASyncTP </a>, <a href="https://github.com/me-no-dev/ESPAsyncWebServer"> ESPAsyncWebServer </a> and <a href="https://github.com/adafruit/Adafruit_NeoPixel"> Adafruit NeoPixel </a> libraries. Unzip the folders, remove the "-master" from the name and move the new folders to the Arduino IDE libraries folder.



### Installation

1. Clone the repo
```sh
git clone https://github.com/mciviletti/LED-wificontrol.git
```
2. Set the parameters in the atmega header file (atmega/led.h) and upload the atmega.ino file to your arduino of choice that will control the LED strips (tested on the ATMega32u4 Sparkfun Pro Micro 5V 16MHz)

3. Open the esp.ino file and use SPIFFS to upload the files in the data folder to your ESP32

4. Set the parameters in the esp header file (esp/led.h) and upload the esp.ino file to your ESP32 dev board.

5. Set the parameters in the esp main file (esp/esp.ino) to connect to your internet (and choose the TX pin).

6. Upload the esp.ino file to your ESP32 board.



## Usage

After uploading the file to the ESP32 board, run the program and check the Serial port for the IP value of the webserver. Type in this IP value on a browser (on a device connected to the same network) to connect to the webserver.

Connect the Arduino RX pin to the ESP32 TX pin of choice (D12 is being used as default). It is not necessary to connect the Arduino's TX pin to the ESP32 RX pin.

Connect the LED_PIN set in atmega/led.h to the D0 of the LED strip. Use a 5V power supply to power the Arduino, ESP32 and the LED strip.

<strong> Remember to set the maximum brightness value in esp/led.h file according to your power supply! </strong> As a rule of thumb, check the power required by your LED strip and compare it to your power supply. If it is bigger, then your maximum brightness must be equal to:
```
powerSupplyWatts/LEDStripWatts * 255
```

...or just get a power supply that can handle the strip at full power and set the maximum brightness to 255.

After everything is setup, using it is very simple. Connect to the server and simply move the respective sliders to set the desired R, G and B values to the strip or the brightness of the strip. Check the boxes for the Rainbow and Pulse animations or use the Color input to select a color directly.

## Comments

As mentioned, the Adafruit NeoPixel library does not work well with the ESP32 - hence the use of the arduino. I used it because I was already familiar with it, but any recommendations of different libraries are appreciated.

The rainbow animation is achieved using a function in Adafruit's example. However, it was altered so that each loop is only one step of the animation, not the whole of it. That way, if the user sends a command to stop, the animation stops immediately.

The pulse animation, however, completes a full cycle each loop. Yeah, I was just lazy about it, will fix in the future so that it is more readily stopped.

I'm aware that the Adafruit library has already built-in functions to control the strip brightness (and I've used it on the rainbow function). However, as mentioned by them in their own source code, their brightness method is destructive - they map the current values with the new brightness but do not store them, so if the brightness value sets any of the RGB values to 0 that value is lost. The way I implemented allows the user to set the brightness to 0 and back and not lose the stored RGB values.


## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request
