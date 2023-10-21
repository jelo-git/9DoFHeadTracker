#include <Arduino.h>
#include "GY_85.h"

GY_85 gy85;

void setup()
{
  Serial.begin(9600);
  gy85.init();
}

void loop()
{
  float x, y, z;
  gy85.readAccel(&x, &y, &z);
  Serial.print("Accel: ");
  Serial.print(x);
  Serial.print(" ");
  Serial.print(y);
  Serial.print(" ");
  Serial.print(z);

  int x2, y2, z2;
  gy85.readGyro(&x2, &y2, &z2);
  Serial.print("\tGyro: ");
  Serial.print(x2);
  Serial.print(" ");
  Serial.print(y2);
  Serial.print(" ");
  Serial.print(z2);

  int x3, y3, z3;
  gy85.readMag(&x3, &y3, &z3);
  Serial.print("\tMag: ");
  Serial.print(x3);
  Serial.print(" ");
  Serial.print(y3);
  Serial.print(" ");
  Serial.println(z3);

  delay(100);
}