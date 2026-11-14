#include <Wire.h>
#include "Adafruit_TCS34725.h"
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);

void setup() {
  Serial.begin(9600);
  
  if (!tcs.begin()) {
    Serial.println("Sensor not found! Check your SDA/SCL wiring.");
    while (1); 
  }
  Serial.println("TCS34725 Ready!");
}

void loop() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c); 

  Serial.print("R: "); Serial.print(r);
  Serial.print(" | G: "); Serial.print(g);
  Serial.print(" | B: "); Serial.println(b);
  if (r > g && r > b) {
    Serial.println("--> Detected Object Color: RED");
  } else if (g > r && g > b) {
    Serial.println("--> Detected Object Color: GREEN");
  } else if (b > r && b > g) {
    Serial.println("--> Detected Object Color: BLUE");
  }
  
  delay(1000); 
}
