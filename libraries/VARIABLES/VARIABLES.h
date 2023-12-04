#include <EEPROM.h>

class sensor_data {
public:
    void setTemp(float value) {
        temp = value;
    }

    void setHumidity(float value) {
        humidity = value;
    }

    void setCO2(int value) {
        co2 = value;
    }

    float getTemp() {
        return temp;
    }

    float getHumidity() {
        return humidity;
    }

    int getCO2() {
        return co2;
    }

private:
    float temp;
    float humidity;
    int co2;
};

class setting_data {
public:
    void setWateringDelay(int delay) {
        watering_delay = delay;
    }

    void setWateringAmount(int amount) {
        watering_amount = amount;
    }

    void setHeatingDelay(int delay) {
        heating_delay = delay;
    }

    void setHeatingTime(int time) {
        heating_time = time;
    }

    void setHeatingThreshold(int threshold) {
        heating_threshold = threshold;
    }

    int getWateringDelay() {
        return watering_delay;
    }

    int getWateringAmount() {
        return watering_amount;
    }

    int getHeatingDelay() {
        return heating_delay;
    }

    int getHeatingTime() {
        return heating_time;
    }

    int getHeatingThreshold() {
        return heating_threshold;
    }

    // Function to save all values to EEPROM
    void saveToEEPROM() {

        EEPROM.put(0, getWateringDelay());
        EEPROM.put(1, getWateringAmount());
        EEPROM.put(2, getHeatingDelay());
        EEPROM.put(3, getHeatingTime());
        EEPROM.put(4, getHeatingThreshold());

        EEPROM.commit();
        delay(10);

    }

    // Function to load all values from EEPROM
    void loadFromEEPROM() {
        int waterDelay;
        int waterAmount;
        int heatingDelay;
        int heatingTime;
        int heatingThreshold;

        EEPROM.get(0, waterDelay);
        EEPROM.get(1, waterAmount);
        EEPROM.get(2, heatingDelay);
        EEPROM.get(3, heatingTime);
        EEPROM.get(4, heatingThreshold);

        setWateringDelay(waterDelay);
        setWateringAmount(waterAmount);
        setHeatingDelay(heatingDelay);
        setHeatingTime(heatingTime);
        setHeatingThreshold(heatingThreshold);
        delay(10);
    }

private:
    int watering_delay;
    int watering_amount;
    int heating_delay;
    int heating_time;
    int heating_threshold;

    // EEPROM address to store the class instance
    static const int EEPROM_ADDRESS = 0;
};




#include "DHT20.h"


#define TEMP_SENSOR_DELAY 500 //ms

sensor_data sensorData;
DHT20 DHT;

class SENSOR {

public:
    void Initialize()
    {
        Wire.begin();
        DHT.begin();

        delay(1000);

        int status = DHT.read();

        switch (status)
        {
            case DHT20_OK:
                Serial.print("OK");
                break;
            case DHT20_ERROR_CHECKSUM:
                Serial.print("Checksum error");
                break;
            case DHT20_ERROR_CONNECT:
                Serial.print("Connect error");
                break;
            case DHT20_MISSING_BYTES:
                Serial.print("Missing bytes");
                break;
            case DHT20_ERROR_BYTES_ALL_ZERO:
                Serial.print("All bytes read zero");
                break;
            case DHT20_ERROR_READ_TIMEOUT:
                Serial.print("Read time out");
                break;
            case DHT20_ERROR_LASTREAD:
                Serial.print("Error read too fast");
                break;
            default:
                Serial.print("Unknown error");
                break;
        }
        Serial.print("\n");


    }

    void Update()
    {

        if (millis() - DHT.lastRead() >= 1000)
        {
            DHT.read();

            sensorData.setTemp(DHT.getTemperature());
            sensorData.setHumidity(DHT.getHumidity());

            Serial.println(DHT.getTemperature());
            Serial.println(DHT.getHumidity());

        }

    }


};
