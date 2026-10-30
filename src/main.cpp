#include "HardwareSerial.h"
#include "WString.h"
#include "esp32-hal.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_HTU21DF.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

<<<<<<< Updated upstream
const char* ssid = "your_ssid_wifi";
const char* password = "your_password";

AsyncWebServer server(80);

=======
// Wi-Fi credentials
const char* ssid = "your_ssid_wifi";
const char* password = "your_password";

// Asynchronous Web Server instance running on HTTP port 80
AsyncWebServer server(80);

// Hardware sensor and display instances
>>>>>>> Stashed changes
Adafruit_HTU21DF htu;
Adafruit_BMP280 bmp;
LiquidCrystal_I2C lcd(0x27, 16, 2);

<<<<<<< Updated upstream
=======
// ==========================================
// --- BASE SENSOR CLASS (POLYMORPHISM) ---
// ==========================================
>>>>>>> Stashed changes
class Sensor {
protected:
    String id, unit, sensor_type;
    float Final_Value;

public:
    Sensor(String _id, String _unit, String _sensor_type)
        : id(_id), unit(_unit), sensor_type(_sensor_type), Final_Value(0.0f) {}

    // Pure virtual method enforcing implementation in all derived sensor classes
    virtual void add_measurement() = 0;

    float get_value() const {
        return Final_Value;
    }

    String get_unit() const{
        return unit;
    }
};

class Temp_Sensor : public Sensor {
private:
    int THR_pin;
    static constexpr float BETA = 3950.0f;

public:
    Temp_Sensor(int pin = 35) : Sensor("Temp_Sensor", "°C", "Thermistor") {
        THR_pin = pin;
    }

    void add_measurement() override {
        int THR = analogRead(THR_pin);

<<<<<<< Updated upstream
=======
        // Safety check to prevent division by zero during open/short circuit conditions
>>>>>>> Stashed changes
        if (THR == 0 || THR >= 4095) {
            Serial.println("Error reading THR (open circuit or short-circuit)");
            return;
        }

<<<<<<< Updated upstream
=======
        // Steinhart-Hart simplified Beta equation for NTC thermistor
>>>>>>> Stashed changes
        float THR_Resistance = 10000.0f * (4095.0f - (float)THR) / (float)THR;
        float tempKelvin = 1.0f / ((1.0f / 298.15f) + (1.0f / BETA) * logf(THR_Resistance / 10000.0f));
        float tempCelsius = tempKelvin - 273.15f;
        Final_Value = tempCelsius;
    }
};

class Luminosity_Sensor : public Sensor {
private:
    int LDR_pin;

public:
    Luminosity_Sensor(int pin = 34) : Sensor("Luminosity_Sensor", "%", "Photoresistor") {
        LDR_pin = pin;
    }

    void add_measurement() override {
        int LDR = analogRead(LDR_pin);
        float LDR_Pourcent = (LDR / 4095.0f) * 100.0f;
        Final_Value = LDR_Pourcent;
    }
};

class Humidity_Sensor : public Sensor {
private:
    Adafruit_HTU21DF* htu;

public:
    Humidity_Sensor(Adafruit_HTU21DF* htu_instance)
        : Sensor("Humidity_Sensor", "%", "HTU21D"), htu(htu_instance) {}

    void add_measurement() override {
        if (htu != nullptr) {
            Final_Value = htu->readHumidity();
        }
    }
};

class Pressure_Sensor : public Sensor {
private:
    Adafruit_BMP280* bmp;

public:
    Pressure_Sensor(Adafruit_BMP280* bmp_instance)
        : Sensor("Pressure_Sensor", "hPa", "BMP280"), bmp(bmp_instance) {}

    void add_measurement() override {
        if (bmp != nullptr) {
            Final_Value = bmp->readPressure() / 100.0f;
        }
    }
};

class Station{
protected:
    String name;
    int nbr_elements;
    Sensor* sensors[4];
    LiquidCrystal_I2C* lcd;

public:
    Station(String _name, LiquidCrystal_I2C* lcd_instance)
        : name(_name), nbr_elements(0), lcd(lcd_instance) {
        for (int i = 0; i < 4; i++){
            sensors[i] = nullptr;
        }
    }
<<<<<<< Updated upstream
    bool add_sensor(Sensor* sensor_instance){
        if (nbr_elements < 4){
=======

    // Attach a new sensor pointer to the array
    bool add_sensor(Sensor* sensor_instance) {
        if (nbr_elements < 4) {
>>>>>>> Stashed changes
            sensors[nbr_elements] = sensor_instance;
            nbr_elements++;
            return true;
        }
        return false;
    }

<<<<<<< Updated upstream
    void update_all(){
        for (int i = 0; i < nbr_elements; i++){
=======
    // Trigger measurement updates for all registered sensors
    void update_all() {
        for (int i = 0; i < nbr_elements; i++) {
>>>>>>> Stashed changes
            if (sensors[i] != nullptr) {
                sensors[i]->add_measurement();
            }
        }
    }
<<<<<<< Updated upstream
    void display(){
        for (int i = 0; i < nbr_elements; i++){
=======

    // Print values to Serial Monitor and format the 1602 LCD layout
    void display() {
        for (int i = 0; i < nbr_elements; i++) {
>>>>>>> Stashed changes
            if (sensors[i] != nullptr) {
                Serial.print(sensors[i]->get_value());
                Serial.print(" ");
                Serial.println(sensors[i]->get_unit());
            }
        }
        if (lcd != nullptr && nbr_elements >= 4) {
                if (sensors[0] != nullptr && sensors[1] != nullptr &&
                    sensors[2] != nullptr && sensors[3] != nullptr) {

                    lcd->clear();

<<<<<<< Updated upstream
                    lcd->setCursor(0, 0);
                    lcd->print("L:");
                    lcd->print((int)sensors[1]->get_value());
                    lcd->print("% ");
=======
                // Row 0: Luminosity (%) and Temperature (°C)
                lcd->setCursor(0, 0);
                lcd->print("L:");
                lcd->print((int)sensors[1]->get_value());
                lcd->print("% ");
>>>>>>> Stashed changes

                    lcd->setCursor(8, 0);
                    lcd->print("T:");
                    lcd->print(sensors[0]->get_value(), 1);
                    lcd->print("C");

<<<<<<< Updated upstream
                    lcd->setCursor(0, 1);
                    lcd->print("H:");
                    lcd->print((int)sensors[2]->get_value());
                    lcd->print("% ");
=======
                // Row 1: Humidity (%) and Pressure (hPa)
                lcd->setCursor(0, 1);
                lcd->print("H:");
                lcd->print((int)sensors[2]->get_value());
                lcd->print("% ");
>>>>>>> Stashed changes

                    lcd->setCursor(8, 1);
                    lcd->print("P:");
                    lcd->print((int)sensors[3]->get_value());
                    lcd->print("hPa");
                }
        }
    }

<<<<<<< Updated upstream
    String to_json(){
=======
    // Generate JSON string payload for REST API endpoint
    String to_json() {
>>>>>>> Stashed changes
        String json = "{";

        if (nbr_elements >= 4) {
            if (sensors[0] != nullptr && sensors[1] != nullptr &&
                sensors[2] != nullptr && sensors[3] != nullptr) {
                json += "\"temp\":" + String(sensors[0]->get_value(), 1) + ",";
                json += "\"lum\":" + String(sensors[1]->get_value(), 0) + ",";
                json += "\"hum\":" + String(sensors[2]->get_value(), 0) + ",";
                json += "\"press\":" + String (sensors[3]->get_value(), 1);
            }
        }
        json += "}";
        return json;
    }
};

<<<<<<< Updated upstream
Station* maStation = nullptr;

=======
// Global Station pointer
Station* maStation = nullptr;

// --- WEB DASHBOARD (HTML/CSS/JS) STORED IN FLASH MEMORY ---
>>>>>>> Stashed changes
const char HTML_INDEX[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Station Météo ESP32</title>
    <style>
        body { font-family: Arial, sans-serif; background: #121212; color: #fff; text-align: center; padding: 20px; }
        h1 { color: #00bcd4; }
        .grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(140px, 1fr)); gap: 15px; max-width: 600px; margin: 20px auto; }
        .card { background: #1e1e1e; padding: 20px; border-radius: 10px; border: 1px solid #333; }
        .val { font-size: 1.6em; font-weight: bold; color: #4caf50; margin-top: 10px; }
    </style>
</head>
<body>
    <h1>Station Météo POO</h1>
    <div class="grid">
        <div class="card">Température<div id="temp" class="val">-- °C</div></div>
        <div class="card">Luminosité<div id="lum" class="val">-- %</div></div>
        <div class="card">Humidité<div id="hum" class="val">-- %</div></div>
        <div class="card">Pression<div id="press" class="val">-- hPa</div></div>
    </div>

    <script>
        async function refresh() {
            try {
                const res = await fetch('/data');
                const data = await res.json();
                document.getElementById('temp').innerText = data.temp + " °C";
                document.getElementById('lum').innerText = data.lum + " %";
                document.getElementById('hum').innerText = data.hum + " %";
                document.getElementById('press').innerText = data.press + " hPa";
            } catch(e) { console.error(e); }
        }
        setInterval(refresh, 2000);
        refresh();
    </script>
</body>
</html>
)rawliteral";

<<<<<<< Updated upstream
void init_wifi_server(){
=======
// ==========================================
// --- WI-FI & ASYNC SERVER INITIALIZATION ---
// ==========================================
void init_wifi_server() {
>>>>>>> Stashed changes
    WiFi.begin(ssid, password);
    Serial.print("Connexion au Wi-Fi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi connecté !");
    Serial.print("Adresse IP : ");
    Serial.println(WiFi.localIP());
<<<<<<< Updated upstream
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", HTML_INDEX);
    });
    server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request) {
            if (maStation != nullptr) {
                request->send(200, "application/json", maStation->to_json());
            } else {
                request->send(500, "text/plain", "Station non initialisee");
            }
=======

    // Root endpoint: Serves HTML web interface from Flash memory
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", HTML_INDEX);
    });

    // API endpoint: Returns JSON string representation of sensor data
    server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (maStation != nullptr) {
            request->send(200, "application/json", maStation->to_json());
        } else {
            request->send(500, "text/plain", "Station not initialized");
        }
>>>>>>> Stashed changes
    });
    server.begin();
}

<<<<<<< Updated upstream
void setup() {
    Serial.begin(115200);
    Wire.begin(21, 22);
    delay(1000);

=======
// ==========================================
// --- SETUP & MAIN LOOP ---
// ==========================================
void setup() {
    Serial.begin(115200);
    Wire.begin(21, 22);
    delay(1000); // Short delay to allow Serial port stabilization

    // Hardware checks to prevent silent execution failures
>>>>>>> Stashed changes
    if (!htu.begin()) {
        Serial.println("Error: HTU21D not detected!");
    }
    if (!bmp.begin(0x76)) {
        Serial.println("Error: BMP280 not detected!");
    }

    lcd.init();
    lcd.backlight();

<<<<<<< Updated upstream
    // Instanciation de la station et ajout des capteurs
=======
    // Instantiate station and attach concrete sensor instances
>>>>>>> Stashed changes
    maStation = new Station("Station_ESP32", &lcd);
    maStation->add_sensor(new Temp_Sensor(35));
    maStation->add_sensor(new Luminosity_Sensor(34));
    maStation->add_sensor(new Humidity_Sensor(&htu));
    maStation->add_sensor(new Pressure_Sensor(&bmp));

    init_wifi_server();
}

void loop() {
    if (maStation != nullptr) {
<<<<<<< Updated upstream
            maStation->update_all();
            maStation->display();
=======
        maStation->update_all();
        maStation->display();
>>>>>>> Stashed changes
    }
    Serial.println(maStation->to_json());
    delay(5000);
}
