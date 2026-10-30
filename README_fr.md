*🌍 [Read this in English](README.md)*

# Station Météo Embarquée - ESP32 (Interface Web & API)

![Photo du montage](img/)

Ce projet est un système embarqué de station météorologique développé sur microcontrôleur ESP32. Basé sur une architecture en **Programmation Orientée Objet (POO)** et intégrant un **serveur web asynchrone**, il mesure en temps réel plusieurs variables environnementales (température, humidité, pression atmosphérique, luminosité) et les restitue simultanément sur un écran LCD 1602 I2C, sur le moniteur série et sur un tableau de bord HTML/JS accessible en réseau local.

## 🛠 Matériel Utilisé

*   **Microcontrôleur :** ESP32 Dev Module
*   **Capteur de Pression :** BMP280 (Interface I2C - Adresse `0x76`) - *Alimentation 3.3V*
*   **Capteur d'Humidité/Température :** HTU21DF / GY-21 (Interface I2C) - *Alimentation 3.3V*
*   **Affichage :** Écran LCD 1602 avec module I2C (Adresse `0x27`) - *Alimentation 5V (VIN/VBUS)*
*   **Capteur de Luminosité :** LDR (Photorésistance) sur broche analogique 34 avec pont diviseur (résistance 10kΩ)
*   **Capteur de Température Ambiante :** Thermistance CTN (BETA = 3950.0) sur broche analogique 35 avec pont diviseur (résistance 10kΩ)

## ⚙️ Architecture & Fonctionnalités Techniques

*   **Conception Orientée Objet (POO) :**
    *   Classe de base abstraite `Sensor` imposant le polymorphisme (`virtual void add_measurement()`).
    *   Classes dérivées spécialisées : `Temp_Sensor`, `Luminosity_Sensor`, `Humidity_Sensor` et `Pressure_Sensor`.
    *   Classe de gestion `Station` encapsulant l'agrégation des capteurs, l'affichage LCD et la génération dynamique du format JSON (`to_json()`).

*   **Serveur Web Asynchrone (`ESPAsyncWebServer`) :**
    *   **Route `/` :** Sert une interface utilisateur HTML/CSS/JS responsive stockée directement dans la mémoire Flash du microcontrôleur (`PROGMEM`).
    *   **Route `/data` :** Expose un endpoint API REST fournissant un objet JSON interrogé toutes les 2 secondes par le client via la Fetch API JavaScript.

*   **Traitement physique des données :**
    *   Conversion de la résistance de la CTN en degrés Celsius par l'équation de Steinhart-Hart simplifiée (paramètre Beta) :
        $$\frac{1}{T} = \frac{1}{T_0} + \frac{1}{\beta} \ln \left( \frac{R}{R_0} \right)$$
    *   Protection contre les lectures invalides et les divisions par zéro sur les canaux ADC.

## 💻 Environnement de Développement

*   **Langage :** C++11 / C++14
*   **Framework :** Arduino / PlatformIO

**Configuration `platformio.ini` :**
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
