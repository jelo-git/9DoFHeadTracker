#include <Arduino.h>

#include <ADXL345.h>

ADXL345 *adxl345;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  adxl345 = new ADXL345();
  Serial.println("ADXL345 init");
}

void loop()
{
  // put your main code here, to run repeatedly:
  float data[3];
  adxl345->readData(data);
  Serial.print("X: ");
  Serial.print(data[0]);
  Serial.print(" Y: ");
  Serial.print(data[1]);
  Serial.print(" Z: ");
  Serial.println(data[2]);
  delay(1000);
}