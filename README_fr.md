*🌍 [Read this in English](README.md)*

# Station Météo Embarquée - ESP32

![Photo du montage](img/)

Ce projet est un système embarqué de station météorologique basé sur un microcontrôleur ESP32. Il collecte en temps réel des données (température, humidité, pression atmosphérique, luminosité) via divers capteurs et les restitue sur un écran LCD via le bus I2C ainsi que sur le moniteur série.

## 🛠 Matériel Utilisé

*   **Microcontrôleur :** ESP32
*   **Capteur de Pression :** BMP280 (Interface I2C - Adresse `0x76`) - *Alimentation 3.3V*
*   **Capteur d'Humidité/Température :** HTU21DF / GY-21 (Interface I2C) - *Alimentation 3.3V*
*   **Affichage :** Écran LCD 1602 avec module I2C (Adresse `0x27`) - *Alimentation 5V (VIN/VBUS)*
*   **Capteur de Luminosité :** LDR (Photorésistance) connectée sur broche analogique avec pont diviseur (résistance 10kΩ)
*   **Capteur de Température Ambiante :** Thermistance CTN (BETA = 3950.0) connectée sur broche analogique avec pont diviseur (résistance 10kΩ)

## ⚙️ Fonctionnalités Techniques

*   **Acquisition Analogique (ADC) :** Lecture et conversion des valeurs brutes de la LDR et de la thermistance avec protection contre les circuits ouverts/courts-circuits (prévention des divisions par zéro).
*   **Communication I2C :** Mutualisation du bus I2C (Broches 21 SDA, 22 SCL) pour l'écran LCD, le BMP280 et le HTU21DF.
*   **Traitement des données :** Application de l'équation de Steinhart-Hart simplifiée (paramètre Beta) pour la conversion de la résistance de la CTN en degrés Celsius :
    $$\frac{1}{T} = \frac{1}{T_0} + \frac{1}{\beta} \ln \left( \frac{R}{R_0} \right)$$
    *Où :*
    *   **$T$** : Température mesurée (en Kelvin, puis convertie en Celsius).
    *   **$T_0$** : Température de référence de la pièce (298.15 K, soit 25°C).
    *   **$\beta$** : Constante thermique du capteur (ici 3950).
    *   **$R$** : Résistance actuelle lue par l'ESP32 (en Ω).
    *   **$R_0$** : Résistance nominale de la thermistance à la température de référence (10 000 Ω).
*   **Gestion des erreurs :** Vérification de l'initialisation des capteurs au démarrage (`setup`) pour éviter les crashs matériels ainsi que les plantages du programme.

## 💻 Environnement de Développement

*   **Langage :** C++
*   **Framework :** Arduino / PlatformIO

**Fichier `platformio.ini` recommandé :**
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

