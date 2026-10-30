*🌍 [Lire en français](README_fr.md)*

# Embedded Weather Station - ESP32 (Multi-Core & Web)

![Hardware Setup Photo](img/)

This project is a multi-tasking embedded weather station based on an ESP32 microcontroller. Designed with **Object-Oriented Programming (OOP)** principles and orchestrated by **FreeRTOS**, it isolates hardware sensor polling on **Core 1** from the asynchronous web server on **Core 0**.

Environmental metrics (temperature, humidity, atmospheric pressure, luminosity) are displayed locally on an I2C LCD screen and broadcasted real-time over the local network via an HTML/JS Web Dashboard and a JSON API.

## 🛠 Hardware Used

*   **Microcontroller:** ESP32 Dev Module
*   **Pressure Sensor:** BMP280 (I2C Interface - Address `0x76`) - *3.3V Power Supply*
*   **Humidity/Temperature Sensor:** HTU21DF / GY-21 (I2C Interface) - *3.3V Power Supply*
*   **Display:** 1602 LCD Screen with I2C module (Address `0x27`) - *5V Power Supply (VIN/VBUS)*
*   **Luminosity Sensor:** LDR (Photoresistor) on analog pin 34 with a voltage divider (10kΩ resistor)
*   **Ambient Temperature Sensor:** NTC Thermistor (BETA = 3950.0) on analog pin 35 with a voltage divider (10kΩ resistor)

## ⚙️ Architecture & Technical Features

*   **Object-Oriented Design (OOP):**
    *   Abstract base class `Sensor` enforcing polymorphism (`virtual void add_measurement()`).
    *   Derived sensor classes: `Temp_Sensor`, `Luminosity_Sensor`, `Humidity_Sensor`, and `Pressure_Sensor`.
    *   `Station` manager class encapsulating the sensor array, batch updates, LCD rendering, and JSON formatting (`to_json()`).

*   **Concurrent Multi-Tasking (FreeRTOS):**
    *   **Core 1 (Hardware Task):** Dedicated `taskSensors` executing I2C/ADC sampling and LCD updates every 2 seconds without CPU stalling (`vTaskDelay`).
    *   **Core 0 (Network Task):** Asynchronous TCP/IP stack and HTTP handling via `ESPAsyncWebServer`.

*   **Thread Safety (Mutex):**
    *   FreeRTOS Mutex semaphore (`xSemaphoreCreateMutex()`) protecting the shared `Station` instance against data races between Core 1 sensor writes and Core 0 HTTP reads.

*   **Web Server & REST API:**
    *   **`/` Route:** Serves a responsive HTML/CSS/JS dashboard stored in Flash memory (`PROGMEM`).
    *   **`/data` Route:** Exposes a JSON data payload updated dynamically every 2 seconds using the client browser's Fetch API.

*   **Physical Data Processing:**
    *   Conversion of NTC thermistor resistance via the simplified Steinhart-Hart Beta equation:
        $$\frac{1}{T} = \frac{1}{T_0} + \frac{1}{\beta} \ln \left( \frac{R}{R_0} \right)$$

## 💻 Development Environment

*   **Language:** C++11 / C++14
*   **Framework:** Arduino / FreeRTOS / PlatformIO

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
