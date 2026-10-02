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

// Broches analogiques (déclarées en global)
const int LDR_Pin = 34;
const int THR_Pin = 35;
const float BETA = 3950.0;

void setup(){
    Wire.begin(21, 22);
    Serial.begin(115200);
    delay(1000); // Petit délai pour laisser le temps au port Série de s'ouvrir

    // Indispensables pour éviter le crash
    if (!htu.begin()) {
        Serial.println("Erreur : capteur HTU21D (GY-21) non detecte !");
    }
    if (!bmp.begin(0x76)) {
        Serial.println("Erreur : capteur BMP280 non detecte !");
    }

    lcd.init();
    lcd.backlight();
}

void loop (){
    // --- LUMINOSITÉ (LDR) ---
    int LDR = analogRead(LDR_Pin);
    float LDR_Pourcent = (LDR / 4095.0F) * 100.0F;

    Serial.print(LDR_Pourcent);
    Serial.println("% de luminosite");

    // --- TEMPÉRATURE AMBIANTE (Thermistor CTN) ---
    int THR = analogRead(THR_Pin);

    // Sécurité pour la thermistance
    if (THR == 0 || THR >= 4095) {
        Serial.println("Erreur de lecture THR (circuit ouvert ou court-circuit)");
        delay(1000);
        return; // Recommence la boucle loop depuis le début
    }

    float THR_Resistance = 10000.0 * (4095.0 - (float)THR) / (float)THR;
    float tempKelvin = 1.0 / ((1.0 / 298.15) + (1.0 / BETA) * log(THR_Resistance / 10000.0));
    float tempCelsius = tempKelvin - 273.15;

    Serial.print(tempCelsius);
    Serial.println(" C");

    // --- HUMIDITÉ (HTU21D) ---
    float GY_hum = htu.readHumidity();
    Serial.print(GY_hum);
    Serial.println("% d'humidite");

    // --- PRESSION (BMP280) ---
    float pressionPa = (bmp.readPressure() / 100.0F);
    Serial.print(pressionPa);
    Serial.println(" hPa");
    Serial.println("-------------------------");

    // --- AFFICHAGE ÉCRAN LCD ---
    lcd.clear();

    // Ligne 0 : Luminosité et Température
    lcd.setCursor(0, 0);
    lcd.print("L:");
    lcd.print((int)LDR_Pourcent);
    lcd.print("% ");

    lcd.setCursor(8, 0);
    lcd.print("T:");
    lcd.print(tempCelsius, 1); // 1 seule décimale
    lcd.print("C");

    // Ligne 1 : Humidité et Pression
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
