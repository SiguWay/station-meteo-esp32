#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_HTU21DF.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal_I2C.h>

<<<<<<< Updated upstream
=======
// Hardware sensor and display instances
>>>>>>> Stashed changes
Adafruit_HTU21DF htu;
Adafruit_BMP280 bmp;
LiquidCrystal_I2C lcd(0x27, 16, 2);

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
    bool add_sensor(Sensor* sensor_instance){
        if (nbr_elements < 4){
            sensors[nbr_elements] = sensor_instance;
            nbr_elements++;
            return true;
        }
        return false;
    }

    void update_all(){
        for (int i = 0; i < nbr_elements; i++){
            if (sensors[i] != nullptr) {
                sensors[i]->add_measurement();
            }
        }
    }
    void display(){
        for (int i = 0; i < nbr_elements; i++){
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

                    lcd->setCursor(0, 0);
                    lcd->print("L:");
                    lcd->print((int)sensors[1]->get_value());
                    lcd->print("% ");

                    lcd->setCursor(8, 0);
                    lcd->print("T:");
                    lcd->print(sensors[0]->get_value(), 1);
                    lcd->print("C");

                    lcd->setCursor(0, 1);
                    lcd->print("H:");
                    lcd->print((int)sensors[2]->get_value());
                    lcd->print("% ");

                    lcd->setCursor(8, 1);
                    lcd->print("P:");
                    lcd->print((int)sensors[3]->get_value());
                    lcd->print("hPa");
                }
        }
    }
};

class Sensor {
protected:
    String id, unit, sensor_type;
    float Final_Value;

public:
    Sensor(String _id, String _unit, String _sensor_type)
        : id(_id), unit(_unit), sensor_type(_sensor_type), Final_Value(0.0f) {}

<<<<<<< Updated upstream
=======
    // Pure virtual function enforcing implementation in all derived sensor classes
>>>>>>> Stashed changes
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
        // Safety check to prevent division by zero during open or short circuit conditions
>>>>>>> Stashed changes
        if (THR == 0 || THR >= 4095) {
            Serial.println("Error reading THR (open circuit or short-circuit)");
            return;
        }

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

<<<<<<< Updated upstream
Station* maStation = nullptr;

void setup() {
    Wire.begin(21, 22);
    Serial.begin(115200);
    delay(1000);
=======
// ==========================================
// --- WEATHER STATION MANAGER CLASS ---
// ==========================================
class Station {
protected:
    String name;
    int nbr_elements;
    Sensor* sensors[4];
    LiquidCrystal_I2C* lcd;

public:
    Station(String _name, LiquidCrystal_I2C* lcd_instance)
        : name(_name), nbr_elements(0), lcd(lcd_instance) {
        for (int i = 0; i < 4; i++) {
            sensors[i] = nullptr;
        }
    }

    // Attach a new sensor pointer to the array
    bool add_sensor(Sensor* sensor_instance) {
        if (nbr_elements < 4) {
            sensors[nbr_elements] = sensor_instance;
            nbr_elements++;
            return true;
        }
        return false;
    }

    // Trigger measurement updates for all registered sensors
    void update_all() {
        for (int i = 0; i < nbr_elements; i++) {
            if (sensors[i] != nullptr) {
                sensors[i]->add_measurement();
            }
        }
    }

    // Print values to Serial Monitor and format the 1602 LCD layout
    void display() {
        for (int i = 0; i < nbr_elements; i++) {
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

                // Row 0: Luminosity (%) and Temperature (°C)
                lcd->setCursor(0, 0);
                lcd->print("L:");
                lcd->print((int)sensors[1]->get_value());
                lcd->print("% ");

                lcd->setCursor(8, 0);
                lcd->print("T:");
                lcd->print(sensors[0]->get_value(), 1);
                lcd->print("C");

                // Row 1: Humidity (%) and Pressure (hPa)
                lcd->setCursor(0, 1);
                lcd->print("H:");
                lcd->print((int)sensors[2]->get_value());
                lcd->print("% ");

                lcd->setCursor(8, 1);
                lcd->print("P:");
                lcd->print((int)sensors[3]->get_value());
                lcd->print("hPa");
            }
        }
    }
};

// Global Station pointer
Station* maStation = nullptr;

// ==========================================
// --- SETUP & MAIN LOOP ---
// ==========================================
void setup() {
    Wire.begin(21, 22);
    Serial.begin(115200);
    delay(1000); // Short delay to allow Serial port stabilization
>>>>>>> Stashed changes

    if (!htu.begin()) {
        Serial.println("Error: HTU21D not detected!");
    }
    if (!bmp.begin(0x76)) {
        Serial.println("Error: BMP280 not detected!");
    }

    lcd.init();
    lcd.backlight();

    // Instanciation de la station et ajout des capteurs
    maStation = new Station("Station_ESP32", &lcd);
    maStation->add_sensor(new Temp_Sensor(35));
    maStation->add_sensor(new Luminosity_Sensor(34));
    maStation->add_sensor(new Humidity_Sensor(&htu));
    maStation->add_sensor(new Pressure_Sensor(&bmp));
}

void loop() {
    if (maStation != nullptr) {
<<<<<<< Updated upstream
            maStation->update_all();
            maStation->display();
        }

        delay(5000);
=======
        maStation->update_all();
        maStation->display();
    }

    delay(5000);
>>>>>>> Stashed changes
}
