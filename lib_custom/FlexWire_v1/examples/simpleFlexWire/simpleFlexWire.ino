// -*- c++ -*-
// Simple sketch to read out one register of an I2C device

#define I2C_7BITADDR 0x68 // DS1307
#define MEMLOC 0x0A
#define ADDRLEN 1

#include <FlexWire_v1.h>

FlexWire flexWire = FlexWire(2, 3);

void setup(void) {
  Serial.begin(57600);
  flexWire.begin();
}

void loop(void){
  flexWire.beginTransmission(I2C_7BITADDR);
  for (byte i=1; i<ADDRLEN; i++) flexWire.write(0x00);
  flexWire.write(MEMLOC);
  flexWire.endTransmission(false);
  flexWire.requestFrom(I2C_7BITADDR,1);
  byte val = flexWire.read();
  Serial.println(val);
  delay(1000);
}
