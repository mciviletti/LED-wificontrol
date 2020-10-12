
#define RX2 16  //ESP32 pin that will serve as RX, not used in current version
#define TX2 12  //ESP32 pin that will serve as TX, sends Serial commands to Arduino

// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "led.h"

// Replace with your network credentials
const char* ssid = "yournetworkname";
const char* password = "yournetworkpassword";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

//Variables to store RGB and brightness values
RGB cor; uint8_t brightness;


// Replaces placeholder with RGB and brightness values
String processor(const String& var){
  Serial.println(var);
  if(var == "RED"){
    return String(cor.R);
  }
  else if (var == "GREEN") {
    return String(cor.G);
  }
  else if (var == "BLUE") {
    return String(cor.B);
  }
  else if (var == "DEFAULT_LIGHT") {
    return String(brightness);
  }
  else if( var == "MAX_LIGHT") {
    return String(MAX_BRIGHTNESS);
  }
  return String();
}


void setup(){
  //Serial com for ESP information
  Serial.begin(115200);
  //Serial2 port sends command to arduino
  Serial2.begin(9600, SERIAL_8N1, 16, 12);

  cor.R = DEFAULT_R;
  cor.G = DEFAULT_G;
  cor.B = DEFAULT_B;
  brightness = DEFAULT_BRIGHTNESS;

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to load style.css file
  server.on("/master.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/master.css", "text/css");
  });

  // Route to load script.js file
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/script.js", "text/javascript");
  });

  // Route to set all 3 colors using Color input in the HTML page
  server.on("/color", HTTP_POST, [](AsyncWebServerRequest *request){
    unsigned long hexvalue;
    AsyncWebParameter* p = request->getParam(0);
    String value = p->value();
    value.remove(0, 1); //Remove # sign
    hexvalue = strtoul(value.c_str(), NULL, 16);
    Serial.print("HEX VALUE RECEIVED: ");
    Serial.println(hexvalue, HEX);
    //Parse RGB values
    cor.R = hexvalue >> 16;
    cor.G = (hexvalue & 0x00FF00) >> 8;
    cor.B = (hexvalue & 0x0000FF);
    //Send to arduino with H prefix
    Serial2.write("H");
    Serial2.write(cor.R);
    Serial2.write(cor.G);
    Serial2.write(cor.B);

  });

  //Route to set R value using Red slider
  server.on("/red", HTTP_POST, [](AsyncWebServerRequest *request){
    AsyncWebParameter* p = request->getParam(0);
    String value = p->value().c_str();
    Serial.println("RED: " + value );
    cor.R = value.toInt();
    Serial2.write("R");
    Serial2.write(cor.R);
  });

  //Route to set G value using Green slider
  server.on("/green", HTTP_POST, [](AsyncWebServerRequest *request){
    AsyncWebParameter* p = request->getParam(0);
    String value = p->value().c_str();
    Serial.println("GREEN: " + value );
    cor.G = value.toInt();
    Serial2.write("G");
    Serial2.write(cor.G);
  });

  //Route to set B value using Blue slider
  server.on("/blue", HTTP_POST, [](AsyncWebServerRequest *request){
    AsyncWebParameter* p = request->getParam(0);
    String value = p->value().c_str();
    Serial.println("BLUE: " + value );
    cor.B = value.toInt();
    Serial2.write("B");
    Serial2.write(cor.B);
  });

  //Route to set Brightness value
  server.on("/light", HTTP_POST, [](AsyncWebServerRequest *request){
    AsyncWebParameter* p = request->getParam(0);
    String value = p->value().c_str();
    Serial.println("LIGHT: " + value);
    brightness = value.toInt();
    Serial2.write("L");
    Serial2.write(brightness);
  });

  //Route to set Rainbow animation
  server.on("/rainbow", HTTP_POST, [](AsyncWebServerRequest *request){
    AsyncWebParameter* p = request->getParam(0);
    String value = p->value().c_str();
    Serial2.write("X");
    if(value == "true") {
      Serial2.write(0xFF);
    }
    else {
      Serial2.write(0x01);
    }
    Serial.println("RAINBOW: " + value);
  });

  server.on("/pulse", HTTP_POST, [](AsyncWebServerRequest *request){
    AsyncWebParameter* p = request->getParam(0);
    String value = p->value().c_str();
    Serial2.write("P");
    if(value == "true") {
      Serial2.write(0xFF);
    }
    else {
      Serial2.write(0x01);
    }
    Serial.println("PULSE: " + value);
  });

  // Start server
  server.begin();
}

void loop(){
  delay(1);
}
