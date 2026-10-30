*🌍 [Read this in English](README.md)*

# Station Météo Embarquée - ESP32 (Multi-Cœur & Web)

![Photo du montage](img/)

Ce projet est un système embarqué de station météorologique multi-tâches basé sur un microcontrôleur ESP32. Développé selon les principes de la **Programmation Orientée Objet (POO)** et orchestré par **FreeRTOS**, il sépare l'acquisition matérielle sur le **Core 1** de la gestion du serveur web asynchrone sur le **Core 0**. 

Les données (température, humidité, pression atmosphérique, luminosité) sont affichées localement sur un écran LCD I2C et distribuées en temps réel sur le réseau local via une interface Web HTML/JS et une API JSON.

## 🛠 Matériel Utilisé

*   **Microcontrôleur :** ESP32 Dev Module
*   **Capteur de Pression :** BMP280 (Interface I2C - Adresse `0x76`) - *Alimentation 3.3V*
*   **Capteur d'Humidité/Température :** HTU21DF / GY-21 (Interface I2C) - *Alimentation 3.3V*
*   **Affichage :** Écran LCD 1602 avec module I2C (Adresse `0x27`) - *Alimentation 5V (VIN/VBUS)*
*   **Capteur de Luminosité :** LDR (Photorésistance) sur broche analogique 34 avec pont diviseur (résistance 10kΩ)
*   **Capteur de Température Ambiante :** Thermistance CTN (BETA = 3950.0) sur broche analogique 35 avec pont diviseur (résistance 10kΩ)

## ⚙️ Architecture & Fonctionnalités Techniques

*   **Conception Orientée Objet (POO) :**
    *   Classe abstraite `Sensor` utilisant le polymorphisme (`virtual void add_measurement()`).
    *   Classes dérivées dédiées : `Temp_Sensor`, `Luminosity_Sensor`, `Humidity_Sensor` et `Pressure_Sensor`.
    *   Classe de gestion `Station` encapsulant la collection de capteurs, la mise à jour globale, l'affichage LCD et la génération dynamique du format JSON (`to_json()`).

*   **Multitâche Concurrent (FreeRTOS) :**
    *   **Core 1 (Tâche Hardware) :** Tâche dédiée `taskSensors` effectuant l'acquisition I2C/ADC et le rafraîchissement LCD toutes les 2 secondes sans bloquer le système (`vTaskDelay`).
    *   **Core 0 (Tâche Réseau) :** Gestion de la pile TCP/IP et du serveur HTTP asynchrone (`ESPAsyncWebServer`).

*   **Sécurisation Mémoire (Mutex) :**
    *   Implémentation d'un sémaphore Mutex (`xSemaphoreCreateMutex()`) pour éviter les *data races* entre l'écriture des capteurs sur le Core 1 et la lecture JSON par les requêtes HTTP sur le Core 0.

*   **Serveur Web & API REST :**
    *   **Route `/` :** Sert un tableau de bord HTML/CSS/JS responsive stocké en mémoire Flash (`PROGMEM`).
    *   **Route `/data` :** Expose une API JSON mise à jour dynamiquement toutes les 2 secondes via la Fetch API du navigateur.

*   **Traitement physique des données :**
    *   Application de l'équation de Steinhart-Hart simplifiée (paramètre Beta) pour la thermistance CTN :
        $$\frac{1}{T} = \frac{1}{T_0} + \frac{1}{\beta} \ln \left( \frac{R}{R_0} \right)$$

## 💻 Environnement de Développement

*   **Langage :** C++11 / C++14
*   **Framework :** Arduino / FreeRTOS / PlatformIO

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
