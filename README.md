*🌍 [Lire en français](README_fr.md)*

# Embedded Weather Station - ESP32 (Web Interface & API)

![Hardware Setup Photo](img/)

This project is an embedded weather station system powered by an ESP32 microcontroller. Built using **Object-Oriented Programming (OOP)** principles and an **asynchronous web server**, it collects environmental metrics (temperature, humidity, atmospheric pressure, luminosity) and outputs them simultaneously to a 1602 I2C LCD display, the serial monitor, and an interactive real-time Web Dashboard.

## 🛠 Hardware Used

* **Microcontroller:** ESP32 Dev Module
* **Pressure Sensor:** BMP280 (I2C Interface - Address `0x76`) - *3.3V Power Supply*
* **Humidity/Temperature Sensor:** HTU21DF / GY-21 (I2C Interface) - *3.3V Power Supply*
* **Display:** 1602 LCD Screen with I2C module (Address `0x27`) - *5V Power Supply (VIN/VBUS)*
* **Luminosity Sensor:** LDR (Photoresistor) on analog pin 34 with a voltage divider (10kΩ resistor)
* **Ambient Temperature Sensor:** NTC Thermistor (BETA = 3950.0) on analog pin 35 with a voltage divider (10kΩ resistor)

## ⚙️ Architecture & Technical Features

* **Object-Oriented Design (OOP):**
  * Abstract base class `Sensor` enforcing polymorphism via `virtual void add_measurement()`.
  * Derived sensor classes: `Temp_Sensor`, `Luminosity_Sensor`, `Humidity_Sensor`, and `Pressure_Sensor`.
  * `Station` manager class handling sensor collection, LCD rendering, and JSON formatting (`to_json()`).

* **Asynchronous Web Server (`ESPAsyncWebServer`):**
  * **`/` Route:** Serves a responsive HTML/CSS/JS user interface stored in Flash memory (`PROGMEM`).
  * **`/data` Route:** Exposes a JSON REST API endpoint continuously polled every 2 seconds by the browser via the JavaScript Fetch API.

* **Analog Data Processing:**
  * Thermistor resistance conversion using the simplified Steinhart-Hart Beta equation.
  * ADC safety checks preventing division by zero during open/short circuit conditions.

## 💻 Development Environment

* **Language:** C++11 / C++14
* **Framework:** Arduino / PlatformIO

**Recommended `platformio.ini`:**

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
lib_deps =
    adafruit/Adafruit BMP280 Library @ ^2.6.8
    adafruit/Adafruit HTU21DF Library @ ^1.1.2
    marcoschwartz/LiquidCrystal_I2C @ ^1.1.4
    me-no-dev/ESP Async WebServer @ ^3.6.0
    me-no-dev/AsyncTCP @ ^3.3.2
