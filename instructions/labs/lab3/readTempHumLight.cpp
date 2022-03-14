/*
  BH1750 library usage example
  This example had some comments about advanced usage features.
  Connection:
    VCC -> 5V (3V3 on Arduino Due, Zero, MKR1000, etc)
    GND -> GND
    SCL -> SCL (A5 on Arduino Uno, Leonardo, etc or 21 on Mega and Due)
    SDA -> SDA (A4 on Arduino Uno, Leonardo, etc or 20 on Mega and Due)
    ADD -> GND or VCC (see below)
  ADD pin uses to set sensor I2C address. If it has voltage greater or equal to
  0.7VCC voltage (as example, you've connected it to VCC) - sensor address will be
  0x5C. In other case (if ADD voltage less than 0.7 * VCC) - sensor address will
  be 0x23 (by default).
*/

/*
 DHT11/22 library usage example
 Connect pin 1 (on the left) of the sensor to +5V or +3V3
 NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
 to 3.3V instead of 5V!
 Connect pin 2 of the sensor to whatever your DHTPIN is
 Connect pin 4 (on the right) of the sensor to GROUND
 Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
*/

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <BH1750.h>
#include <Wire.h>

#define DHTPIN 2     // what digital pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

BH1750 lightMeter(0x23);

float h;
float t;

uint32_t lux;


void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();

  // begin returns a boolean that can be used to detect setup problems.
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println(F("BH1750 Advanced begin"));
  } else {
    Serial.println(F("Error initialising BH1750"));
  }

}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }


  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.println(t);

  lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");

}
