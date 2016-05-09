// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ADC121C_ACS714
// This code is designed to work with the ADC121C_I2CS_ACS714 I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Hall-Effect?sku=ADC121C_I2CS_ACS714

#include <Wire.h>

// ADC121C_ACS714 I2C address is 0x50(80)
#define Addr 0x50

void setup()
{
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select configuration register
  Wire.write(0x02);
  // Automatic conversion mode enabled
  Wire.write(0x20);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(300);
}

void loop()
{
  unsigned int data[2];
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x00);
  // Stop I2C transmission
  Wire.endTransmission();
  
  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);
  
  // Read 2 bytes of data
  // raw_adc msb, raw_adc lsb
  if(Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }
  
  // Convert the data to 12-bits
  int raw_adc = ((data[0] & 0x0F) * 256) + data[1];
  float current = raw_adc / 1000.0;
  
  // Output data to serial monitor
  Serial.print("Instantaneous Current value : ");
  Serial.print(current);
  Serial.println(" A");
  delay(500);
}


