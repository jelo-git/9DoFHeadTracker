#include <Arduino.h>
#include "GY_85.h"
// #include "filter.h"

// #define WEIGHT 0.2
#define ALPHA 0.2

GY_85 gy85;

float gxang, gyang, gzang, previous_time;

void setup()
{
  Serial.begin(9600);
  gy85.init();
  gxang = 0.0;
  gyang = 0.0;
  gzang = 0.0;
  previous_time = 0.0;
}

void loop()
{
  // accelerometer
  int ax, ay, az;
  gy85.readAccel(&ax, &ay, &az);
  double aroll = atan2(ay, az) * 180 / PI;
  double apitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180 / PI;

  // gyroscope
  int gx, gy, gz;
  float current_time = millis();
  float elapsed = (current_time - previous_time) / 1000.0;
  gy85.readGyro(&gx, &gy, &gz);
  gxang += (float)gx * elapsed; // roll
  gyang += (float)gy * elapsed; // pitch
  gzang += (float)gz * elapsed; // yaw
  previous_time = current_time;

  // magnetometer
  int mx, my, mz;
  gy85.readMag(&mx, &my, &mz);
  double myaw = atan2(-my, mx) * 180 / PI;

  // fuse data
  double roll = (1 - ALPHA) * gxang + ALPHA * aroll;
  double pitch = (1 - ALPHA) * gyang + ALPHA * apitch;
  double yaw = (1 - ALPHA) * gzang + ALPHA * myaw;
  Serial.print(roll);
  Serial.print(" ");
  Serial.print(pitch);
  Serial.print(" ");
  Serial.println(yaw);

  // delay(10);
}