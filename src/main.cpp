#include <Arduino.h>
#include <Wire.h>
//-----------------------------------------
#include <Adafruit_HTU21DF.h>
Adafruit_HTU21DF htu = Adafruit_HTU21DF();
//----------------------------------------
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp;
//-----------------------------------------
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Analog pins (declared globally)
const int LDR_Pin = 34;
const int THR_Pin = 35;
const float BETA = 3950.0;

void setup(){
    Wire.begin(21, 22);
    Serial.begin(115200);
    delay(1000); // Short delay to allow the Serial port to open

    // Essential checks to prevent hardware crashes
    if (!htu.begin()) {
        Serial.println("Error: HTU21D (GY-21) sensor not detected!");
    }
    if (!bmp.begin(0x76)) {
        Serial.println("Error: BMP280 sensor not detected!");
    }

    lcd.init();
    lcd.backlight();
}

void loop (){
    // --- LUMINOSITY (LDR) ---
    int LDR = analogRead(LDR_Pin);
    float LDR_Pourcent = (LDR / 4095.0F) * 100.0F;

    Serial.print(LDR_Pourcent);
    Serial.println("% luminosity");

    // --- AMBIENT TEMPERATURE (NTC Thermistor) ---
    int THR = analogRead(THR_Pin);

    // Safety check for the thermistor
    if (THR == 0 || THR >= 4095) {
        Serial.println("Error reading THR (open circuit or short-circuit)");
        delay(1000);
        return; // Restarts the loop from the beginning
    }

    float THR_Resistance = 10000.0 * (4095.0 - (float)THR) / (float)THR;
    float tempKelvin = 1.0 / ((1.0 / 298.15) + (1.0 / BETA) * log(THR_Resistance / 10000.0));
    float tempCelsius = tempKelvin - 273.15;

    Serial.print(tempCelsius);
    Serial.println(" C");

    // --- HUMIDITY (HTU21D) ---
    float GY_hum = htu.readHumidity();
    Serial.print(GY_hum);
    Serial.println("% humidity");

    // --- PRESSURE (BMP280) ---
    float pressionPa = (bmp.readPressure() / 100.0F);
    Serial.print(pressionPa);
    Serial.println(" hPa");
    Serial.println("-------------------------");

    // --- LCD DISPLAY ---
    lcd.clear();

    // Row 0: Luminosity and Temperature
    lcd.setCursor(0, 0);
    lcd.print("L:");
    lcd.print((int)LDR_Pourcent);
    lcd.print("% ");

    lcd.setCursor(8, 0);
    lcd.print("T:");
    lcd.print(tempCelsius, 1); // 1 decimal place only
    lcd.print("C");

    // Row 1: Humidity and Pressure
    lcd.setCursor(0, 1);
    lcd.print("H:");
    lcd.print((int)GY_hum);
    lcd.print("% ");

    lcd.setCursor(8, 1);
    lcd.print("P:");
    lcd.print((int)pressionPa);
    lcd.print("hPa");

    delay(5000);
}
