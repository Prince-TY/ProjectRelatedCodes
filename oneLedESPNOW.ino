
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

const int buttonPin = 23;

// Receiver MAC: 10:06:1C:66:07:64
uint8_t receiverAddress[] = {
  0x10, 0x06, 0x1C, 0x66, 0x07, 0x64
};

uint8_t ledState = 0;

int lastButtonReading = HIGH;
int stableButtonState = HIGH;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

bool readyToSend = false;

void setup() {
  Serial.begin(115200);

  pinMode(buttonPin, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);

  // Both ESP32 boards must use channel 1
  esp_err_t ch = esp_wifi_set_channel(
    1, WIFI_SECOND_CHAN_NONE
  );

  Serial.print("Sender MAC: ");
  Serial.println(WiFi.macAddress());

  if (ch != ESP_OK) {
    Serial.println("Failed to set Wi-Fi channel!");
    return;
  }

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW initialization failed!");
    return;
  }

  esp_now_peer_info_t peerInfo = {};

  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 1;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add receiver!");
    return;
  }

  readyToSend = true;
  Serial.println("Sender ready. Press the button.");
}

void loop() {
  if (!readyToSend) {
    delay(100);
    return;
  }

  int reading = digitalRead(buttonPin);

  if (reading != lastButtonReading) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > debounceDelay) {
    if (reading != stableButtonState) {
      stableButtonState = reading;

      // Button pressed: GPIO 23 becomes LOW
      if (stableButtonState == LOW) {
        ledState = !ledState;

        esp_err_t result = esp_now_send(
          receiverAddress,
          &ledState,
          sizeof(ledState)
        );

        Serial.print("Command: ");
        Serial.println(ledState ? "LED ON" : "LED OFF");

        if (result != ESP_OK) {
          Serial.println("Send request failed!");
        }
      }
    }
  }

  lastButtonReading = reading;
}
