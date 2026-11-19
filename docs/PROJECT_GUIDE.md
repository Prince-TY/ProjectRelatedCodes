# Project Guide

This guide contains practical setup and test notes for the sketches in this repository.

## General Arduino workflow

1. Open Arduino IDE.
2. Open the project's primary `.ino` file. Its containing sketch folder has the same name as the file.
3. Install the required board package and libraries.
4. Select the exact board model and COM port.
5. Compile before uploading.
6. Open Serial Monitor at the baud rate used by the sketch.
7. Test one feature at a time and record the result.

## Button Toggle

**Pins**
- Button signal: GPIO 21
- LED output: GPIO 23
- Button wiring: GPIO 21 to one side of a normally-open push button; other side to GND.

**Test**
- Upload the sketch.
- Press and release the button once.
- The LED should change state once per press.
- If one press produces multiple toggles, improve the debounce logic.

## TCS34725 Colour Sensor

**Connections**
- VIN / VCC: use the voltage specified by your breakout-board manufacturer.
- GND: common ground.
- SDA and SCL: the board's I2C SDA and SCL pins.

**Test**
- Install Adafruit TCS34725 library.
- Upload and open Serial Monitor at 9600 baud.
- Confirm that the sensor is detected and that RGB readings change when objects are placed in front of it.

**Limitation**
The current sketch compares raw channel magnitudes. Ambient light, distance, surface finish, and sensor gain can affect the result. Calibrate thresholds and lighting conditions for a more reliable application.

## ESP-NOW LED sender and receiver

**Receiver**
- Upload the receiver sketch.
- Open Serial Monitor at 115200 baud.
- Copy the printed receiver MAC address.
- The current receiver output pin is GPIO 2; verify that this pin controls the intended LED on your board.

**Sender**
- Replace the six bytes in `receiverAddress` with the receiver's MAC address.
- Connect a normally-open push button between GPIO 23 and GND.
- Upload the sender sketch to the second ESP32.

**Test**
- Confirm both boards initialize ESP-NOW successfully.
- Keep both boards configured for Wi-Fi channel 1.
- Press the sender button. The receiver should report the received state and switch its LED.
- If no messages arrive, re-check the MAC address, channel, power, and board compatibility.

## Blynk dual LED control

**Datastreams**
- V0: integer datastream for the white LED.
- V1: integer datastream for the second LED.

**Pins**
- White LED: GPIO 22.
- Second LED: GPIO 23.

**Credentials setup**
1. Copy `secrets.example.h` to `secrets.h` in this sketch folder.
2. Fill in the values from your Blynk device and Wi-Fi network.
3. Keep `secrets.h` private. It is ignored by Git.
4. Upload the sketch and verify the connection in Serial Monitor.

Use suitable series resistors for discrete LEDs. Do not connect motors, pumps, relays, or other high-current loads directly to ESP32 GPIO pins.

## Recording test results

For each project, record:
- Board model and core version.
- Library versions.
- Supply voltage.
- Wiring changes.
- Compile and upload result.
- Observed behavior and any remaining issues.
