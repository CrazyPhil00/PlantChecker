#include <Arduino.h>
#include "VARIABLES.h"
#include "SENSOR.h"
#include "MENU.h"








/*-------------TODO----------------

----------MODULES/SENSORS----------

Temp Sensor GPIO22/GPIO21
Humidity Sensor 
2 Moisture Sensor GPIO22/GPIO21
CO2 Sensor

RTC
2 Relais (Water Pump, Heater) GPIO12/GPIO14
SD Module

OLED 
Button GPIO25/GPIO26/GPIO27
Potentiometer


-----------CODE-FUNCTION-----------

1. Initialize Modules and Sensors.
2. Get Temperature, Humidity, Moisture and CO2 Values and write them to the SD card with the time of the RTC. 
3. ? Start displaying Information on the OLED (Temperature, Humidity and CO2 Level)
4. Check moisture, if value is under threshould start watering. The ON time of the pump is set by a specific Liter amount which is set using the OLED. 
   Wait a given amount for next value reading. (should be over 30min so the plants don't get watered to much)
5. Check for Temperature, Humidity and CO2 levels, if one of the three is too low (or too high), turn on the Relai for the heater. (Heater should be on and off for at least 5min)
6. Log all data of the sensors.

7. ? When one of the button is pressed a menu gets toggled. It shows multiple Menus with which the user can change settings. 
7.0 Rotary encoder scrolls menu and changes values, button enters or saves (exits) a menu.
7.1 The first Menu is the Moisture threshould. It decides whenever the pump should turn on. (in %, 0%=Dry, 100%=wet)
7.2 Second Menu sets the watering amount, set in Liters. (First need to calibrate it)
7.3 Third Menu sets the minimal Temperature. (Temp when the Heater starts in C°)
7.4 Fourth Menu sets the maximal Temperature. (Temp when the Heater stops in C°)
7.5 Fift Menu sets the minimal CO2 Level. (PPM)
7.6 Sixth Menu sets the time for the Heater (Minutes)
7.7 If no button gets pressed after 1 Minutes the Menus close and the normal Information gets displayed.
-----------------------------------*/


MENU menu;
setting_data settings;
sensor_data sensor_values;
SENSOR _sensor;



const int MOISTURE_SENSOR_1 = 34;
const int MOISTURE_SENSOR_2 = 35;
const int GAS_SENSOR = 32;

const int RELAY_HEATER = 12;
const int RELAY_PUMP = 14;




void setup() {

  Serial.begin(115200);
  
  Wire.begin();


  pinMode(GAS_SENSOR, INPUT);

  pinMode(BUTTON_UP, INPUT);
  pinMode(BUTTON_DOWN, INPUT);
  pinMode(BUTTON_ENTER, INPUT);

  pinMode(RELAY_HEATER, OUTPUT);
  pinMode(RELAY_PUMP, OUTPUT);

  menu.Initialize();

  _sensor.Initialize();
  
}

void loop() {

  menu.render();

  _sensor.Update();

  //Serial.println(sensor_values.getTemp());
  //Serial.println(sensor_values.getHumidity());

}





