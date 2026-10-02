*🌍 [Lire en français](README_fr.md)*

# Embedded Weather Station - ESP32

![Hardware Setup Photo](img/)

This project is an embedded weather station system based on an ESP32 microcontroller. It collects real-time environmental data (temperature, humidity, atmospheric pressure, luminosity) via various sensors and displays it on a 1602 LCD screen via the I2C bus, as well as on the serial monitor.

## 🛠 Hardware Used

*   **Microcontroller:** ESP32
*   **Pressure Sensor:** BMP280 (I2C Interface - Address `0x76`) - *3.3V Power Supply*
*   **Humidity/Temperature Sensor:** HTU21DF / GY-21 (I2C Interface) - *3.3V Power Supply*
*   **Display:** 1602 LCD Screen with I2C module (Address `0x27`) - *5V Power Supply (VIN/VBUS)*
*   **Luminosity Sensor:** LDR (Photoresistor) connected to an analog pin with a voltage divider (10kΩ resistor)
*   **Ambient Temperature Sensor:** NTC Thermistor (BETA = 3950.0) connected to an analog pin with a voltage divider (10kΩ resistor)

## ⚙️ Technical Features

*   **Analog Acquisition (ADC):** Reading and converting raw values from the LDR and thermistor, including protection against open/short circuits (preventing division by zero).
*   **I2C Communication:** I2C bus sharing (Pins 21 SDA, 22 SCL) to seamlessly manage the LCD screen, BMP280, and HTU21DF on the same data line.
*   **Data Processing:** Application of the simplified Steinhart-Hart equation (Beta parameter) to convert the NTC resistance into degrees Celsius:
    $$\frac{1}{T} = \frac{1}{T_0} + \frac{1}{\beta} \ln \left( \frac{R}{R_0} \right)$$
    *Where:*
    *   **$T$**: Measured temperature (in Kelvin, then converted to Celsius).
    *   **$T_0$**: Reference room temperature (298.15 K, or 25°C).
    *   **$\beta$**: Thermal constant of the sensor (3950).
    *   **$R$**: Current resistance read by the ESP32 (in Ω).
    *   **$R_0$**: Nominal resistance of the thermistor at the reference temperature (10,000 Ω).
*   **Error Management:** Sensor initialization check at startup (`setup`) to prevent hardware crashes and program stalls (LoadProhibited panics).

## 💻 Development Environment

*   **Language:** C++
*   **Framework:** Arduino / PlatformIO
*(Note: A task configuration for the Zed editor is natively included in this repository)*

**Recommended `platformio.ini` file:**
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
