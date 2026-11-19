# Project Related Codes

A collection of practical embedded-systems projects built with Arduino-compatible boards, ESP32, sensors, wireless communication, and IoT platforms.

The repository is organized so each project has its own folder, clear purpose, hardware notes, and setup instructions. It is intended as a learning portfolio and a starting point for further robotics, automation, and IoT development.

## Projects

| Project | Board / hardware | What it does |
|---|---|---|
| [Button Toggle](projects/button-toggle/Button_Toggle/Button_Toggle.ino) | ESP32 or compatible board | Toggles an LED each time a push button is pressed. |
| [TCS34725 Colour Sensor](projects/color-sensor/Color_sensor_code/Color_sensor_code.ino) | Board with I2C | Reads raw red, green, and blue values and makes a basic colour estimate. |
| [ESP-NOW LED Receiver](projects/esp-now-led/receiver/led/led.ino) | ESP32 | Receives a one-byte LED state over ESP-NOW and controls an LED. |
| [ESP-NOW Button Sender](projects/esp-now-led/sender/oneLedESPNOW/oneLedESPNOW.ino) | ESP32 | Toggles a state with a debounced button and sends it to the receiver. |
| [Blynk Dual LED Control](projects/blynk-led/ledsblynk/ledsblynk.ino) | ESP32, Wi-Fi, Blynk | Controls two LEDs from Blynk virtual pins V0 and V1. |

## Repository structure

```text
ProjectRelatedCodes/
├── README.md
├── .gitignore
├── docs/
│   └── PROJECT_GUIDE.md
└── projects/
    ├── button-toggle/
    │   └── Button_Toggle/
    │       └── Button_Toggle.ino
    ├── color-sensor/
    │   └── Color_sensor_code/
    │       └── Color_sensor_code.ino
    ├── esp-now-led/
    │   ├── receiver/
    │   │   └── led/
    │   │       └── led.ino
    │   └── sender/
    │       └── oneLedESPNOW/
    │           └── oneLedESPNOW.ino
    └── blynk-led/
        └── ledsblynk/
            ├── ledsblynk.ino
            └── secrets.example.h
```

## Getting started

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Install the board support package for the board used by the project (for ESP32 projects, install **esp32 by Espressif Systems** using Boards Manager).
3. Open the relevant `.ino` file in Arduino IDE. Keep the sketch folder and primary `.ino` file with the same name.
4. Install the libraries listed for that project below.
5. Select the correct board and serial port, connect the hardware, then compile and upload.
6. Read the project-specific notes in [docs/PROJECT_GUIDE.md](docs/PROJECT_GUIDE.md) before powering the circuit.

## Project setup and libraries

### 1. Button Toggle
- Main file: `projects/button-toggle/Button_Toggle/Button_Toggle.ino`
- Uses the Arduino core only.
- Current pin assignments: button on GPIO 21 and LED on GPIO 23.
- The button is configured as `INPUT_PULLUP`; connect it between GPIO 21 and GND.

### 2. TCS34725 Colour Sensor
- Main file: `projects/color-sensor/Color_sensor_code/Color_sensor_code.ino`
- Library: **Adafruit TCS34725** (install through Arduino IDE Library Manager; install dependencies if prompted).
- Uses I2C through the board's SDA and SCL pins.
- The sketch reports raw RGB readings and applies a simple largest-channel comparison. This is a basic demonstration, not calibrated colour measurement.

### 3. ESP-NOW LED Control
- Receiver: `projects/esp-now-led/receiver/led/led.ino`
- Sender: `projects/esp-now-led/sender/oneLedESPNOW/oneLedESPNOW.ino`
- Both sketches require an ESP32 board package and the ESP-NOW libraries included with it.
- Upload the receiver first and read its MAC address from Serial Monitor.
- Update `receiverAddress` in the sender sketch to match the receiver's MAC address.
- The sender and receiver are configured for Wi-Fi channel 1. Keep both devices on the same channel.
- The receiver sketch uses the newer ESP-NOW receive callback API. If compilation fails, check that your ESP32 Arduino core version supports this callback signature.

### 4. Blynk Dual LED Control
- Main file: `projects/blynk-led/ledsblynk/ledsblynk.ino`
- Library: **Blynk** (install through Arduino IDE Library Manager).
- Create a Blynk template/device and configure datastreams V0 and V1 as integer values for the two LEDs.
- Copy `secrets.example.h` to `secrets.h` in the same sketch folder, then enter your own template ID, template name, device auth token, Wi-Fi SSID, and Wi-Fi password in `secrets.h`.
- Never commit `secrets.h` or paste credentials into public source files. The repository's `.gitignore` excludes it.

## Security

This repository is public. Do not commit Wi-Fi passwords, API keys, device tokens, private certificates, or other credentials. If a credential has ever been committed, revoke or rotate it: deleting it from the latest file does not remove it from earlier Git commits.

## Development notes

- Each project is kept independent; upload only the sketch you are currently testing.
- Pin assignments may need adjustment for your exact board and wiring.
- Test low-voltage circuits with current-limited or otherwise suitable power supplies before connecting external loads.
- Hardware and software have not been certified for safety-critical applications.
- Add new projects under `projects/` with a dedicated folder, a descriptive sketch name, and setup notes in this README or the project guide.

## Contributing / extending

Suggestions, bug fixes, wiring diagrams, test results, and additional embedded-systems projects are welcome. When adding a project, include:
1. A short purpose statement.
2. Board and component list.
3. Pin mapping and wiring notes.
4. Required libraries and board-core version, where relevant.
5. Upload and testing instructions.
6. Photos or diagrams where they clarify the build.

## Author

**PRINCE Tuyishime**

Embedded systems • Arduino • ESP32 • IoT • Robotics and automation

---

*This repository is a growing collection of learning projects. Always verify wiring and library compatibility with your exact hardware before uploading.*
