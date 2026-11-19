
#include <WiFi.h>
#include <esp_now.h>

const int ledPin = 2;

// Shared between the ESP-NOW callback and loop
volatile int receivedLedState = -1;

void onDataReceived(const esp_now_recv_info_t *info,
                    const uint8_t *data,
                    int len) {
  if (len == sizeof(uint8_t)) {
    receivedLedState = data[0];
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.mode(WIFI_STA);

  Serial.print("Receiver MAC Address: ");
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW initialization failed!");
    return;
  }

  esp_now_register_recv_cb(onDataReceived);

  Serial.println("Receiver ready! Waiting for button...");
}

void loop() {
  int state = receivedLedState;

  if (state != -1) {
    digitalWrite(ledPin, state ? HIGH : LOW);

    Serial.print("LED is ");
    Serial.println(state ? "ON" : "OFF");

    receivedLedState = -1;
  }
}
