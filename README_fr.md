*🌍 [Read this in English](README.md)*

<<<<<<< Updated upstream
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
=======
# Station Météo Embarquée - ESP32 (Socle POO & LCD)

![Photo du montage](img/)

Ce projet est un système embarqué de station météorologique développé sur microcontrôleur ESP32. Basé sur une architecture robuste en **Programmation Orientée Objet (POO)**, il mesure en temps réel les variables environnementales (température, humidité, pression atmosphérique, luminosité) et les affiche simultanément sur un écran LCD 1602 I2C et sur le moniteur série.

## 🛠 Matériel Utilisé

* **Microcontrôleur :** ESP32 Dev Module
* **Capteur de Pression :** BMP280 (Interface I2C - Adresse `0x76`) - *Alimentation 3.3V*
* **Capteur d'Humidité/Température :** HTU21DF / GY-21 (Interface I2C) - *Alimentation 3.3V*
* **Affichage :** Écran LCD 1602 avec module I2C (Adresse `0x27`) - *Alimentation 5V (VIN/VBUS)*
* **Capteur de Luminosité :** LDR (Photorésistance) sur broche analogique 34 avec pont diviseur (résistance 10kΩ)
* **Capteur de Température Ambiante :** Thermistance CTN (BETA = 3950.0) sur broche analogique 35 avec pont diviseur (résistance 10kΩ)
>>>>>>> Stashed changes

## ⚙️ Fonctionnalités Techniques

<<<<<<< Updated upstream
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
=======
* **Conception Orientée Objet (POO) :**
  * Classe de base abstraite `Sensor` imposant le polymorphisme (`virtual void add_measurement()`).
  * Classes dérivées spécialisées : `Temp_Sensor`, `Luminosity_Sensor`, `Humidity_Sensor` et `Pressure_Sensor`.
  * Classe de gestion `Station` encapsulant l'agrégation dynamique des capteurs (tableau de pointeurs) et l'affichage formaté sur l'écran LCD 1602.

* **Traitement physique des données :**
  * Conversion de la résistance de la CTN en degrés Celsius par l'équation de Steinhart-Hart simplifiée (paramètre Beta).
  * Vérification de sécurité sur les canaux ADC pour éviter toute division par zéro en cas de court-circuit ou circuit ouvert.

## 💻 Environnement de Développement

* **Langage :** C++11 / C++14
* **Framework :** Arduino / PlatformIO

**Configuration `platformio.ini` :**

>>>>>>> Stashed changes
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
