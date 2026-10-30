*🌍 [Lire en français](README_fr.md)*

<<<<<<< Updated upstream
# Embedded Weather Station - ESP32

![Hardware Setup Photo](img/)

This project is an embedded weather station system based on an ESP32 microcontroller. It collects real-time environmental data (temperature, humidity, atmospheric pressure, luminosity) via various sensors and displays it on a 1602 LCD screen via the I2C bus, as well as on the serial monitor.
=======
# Embedded Weather Station - ESP32 (OOP Base & LCD)

![Hardware Setup Photo](img/)

This project is an embedded weather station system powered by an ESP32 microcontroller. Built upon a clean **Object-Oriented Programming (OOP)** architecture, it measures real-time environmental data (temperature, humidity, atmospheric pressure, luminosity) and outputs it simultaneously to a 1602 I2C LCD display and the serial monitor.
>>>>>>> Stashed changes

## 🛠 Hardware Used

*   **Microcontroller:** ESP32
*   **Pressure Sensor:** BMP280 (I2C Interface - Address `0x76`) - *3.3V Power Supply*
*   **Humidity/Temperature Sensor:** HTU21DF / GY-21 (I2C Interface) - *3.3V Power Supply*
*   **Display:** 1602 LCD Screen with I2C module (Address `0x27`) - *5V Power Supply (VIN/VBUS)*
*   **Luminosity Sensor:** LDR (Photoresistor) connected to an analog pin with a voltage divider (10kΩ resistor)
*   **Ambient Temperature Sensor:** NTC Thermistor (BETA = 3950.0) connected to an analog pin with a voltage divider (10kΩ resistor)

## ⚙️ Technical Features

<<<<<<< Updated upstream
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
*   **Error Management:** Sensor initialization check at startup (`setup`) to prevent hardware crashes and program stalls.
=======
* **Object-Oriented Design (OOP):**
  * Abstract base class `Sensor` enforcing polymorphism via `virtual void add_measurement()`.
  * Derived sensor classes: `Temp_Sensor`, `Luminosity_Sensor`, `Humidity_Sensor`, and `Pressure_Sensor`.
  * `Station` manager class handling sensor array aggregation and formatted LCD output rendering.

* **Analog Data Processing:**
  * Thermistor resistance conversion using the simplified Steinhart-Hart Beta equation.
  * ADC safety checks preventing division by zero during open or short circuit conditions.
>>>>>>> Stashed changes

## 💻 Development Environment

*   **Language:** C++
*   **Framework:** Arduino / PlatformIO

**Recommended `platformio.ini` file:**
```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
lib_deps =
<<<<<<< Updated upstream
  adafruit/Adafruit BMP280 Library @ ^2.6.8
  adafruit/Adafruit HTU21DF Library @ ^1.1.2
  marcoschwartz/LiquidCrystal_I2C @ ^1.1.4
=======
    adafruit/Adafruit BMP280 Library @ ^2.6.8
    adafruit/Adafruit HTU21DF Library @ ^1.1.2
    marcoschwartz/LiquidCrystal_I2C @ ^1.1.4
>>>>>>> Stashed changes
