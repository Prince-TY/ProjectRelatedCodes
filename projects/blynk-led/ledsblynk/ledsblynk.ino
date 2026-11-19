#include "secrets.h"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// LED pins
#define WHITE_LED 22
#define SECOND_LED 23

// Control white LED from Blynk V0
BLYNK_WRITE(V0)
{
  int value = param.asInt();

  digitalWrite(WHITE_LED, value);

  if (value == 1)
  {
    Serial.println("White LED: ON");
  }
  else
  {
    Serial.println("White LED: OFF");
  }
}

// Control second LED from Blynk V1
BLYNK_WRITE(V1)
{
  int value = param.asInt();

  digitalWrite(SECOND_LED, value);

  if (value == 1)
  {
    Serial.println("Second LED: ON");
  }
  else
  {
    Serial.println("Second LED: OFF");
  }
}

// When Blynk connects
BLYNK_CONNECTED()
{
  Serial.println("Blynk connected successfully!");
}

void setup()
{
  Serial.begin(115200);

  pinMode(WHITE_LED, OUTPUT);
  pinMode(SECOND_LED, OUTPUT);

  digitalWrite(WHITE_LED, LOW);
  digitalWrite(SECOND_LED, LOW);

  Serial.println();
  Serial.println("ESP32 LED CONTROL STARTING...");

  Serial.print("Connecting to WiFi: ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected successfully!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Connecting to Blynk...");

  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);
}

void loop()
{
  Blynk.run();
}
