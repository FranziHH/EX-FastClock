/* 
 * Demonstrate that we can replace Wire and use multiple instances to implement multiple I2C buses.
 * We use the Sparkfun library for the HTU21D temp/humidity sensor to demonstrate that
*/

#define SHARESCL 1
#define SWITCHPINS 1

#include <FlexWire_v1.h>
#include <SparkFunHTU21D.h>

#define MAXSENSOR 2

// The pins are we are going to use for the I2C buses
uint8_t sdapin[MAXSENSOR] = { 2, 4 };
#if SHARESCL
const uint8_t sclpin = 3;
#else
uint8_t sclpin[MAXSENSOR] = { 3, 5 };
#endif

#if SWITCHPINS
FlexWire flexWire;
HTU21D htu;
#else 
// Array of Flexwire instances
#if SHARESCL
FlexWire flexWire[MAXSENSOR] = { {sdapin[0], sclpin}, {sdapin[1], sclpin} }; 
#else
FlexWire flexWire[MAXSENSOR] = { {sdapin[0], sclpin[0]}, {sdapin[1], sclpin[1]} }; 
#endif
// Create array of instances of the HTU21D class
HTU21D htu[MAXSENSOR];
#endif

void setup()
{
  Serial.begin(9600);
  Serial.println(F("Multi-I2C example with HTU21D"));
#if SWITCHPINS
  for (uint8_t i=0; i < MAXSENSOR; i++) {
    flexWire.setPins(sdapin[i], sclpin);
    htu.begin();
  }
  flexWire.setClock(90000);
#else
  for (uint8_t i=0; i < MAXSENSOR; i++) htu[i].begin(flexWire[i]);
#endif
}

void loop()
{
  for (uint8_t i=0; i < MAXSENSOR; i++) {
    Serial.print(F("Sensor "));
    Serial.print(i+1);
    Serial.print(F(": "));
#if SWITCHPINS
    flexWire.setPins(sdapin[i], sclpin);
    Serial.print(htu.readTemperature(), 1);
#else
    Serial.print(htu[i].readTemperature(), 1);
#endif
    Serial.println("C");
  }
  Serial.println();
  delay(1000);
}
