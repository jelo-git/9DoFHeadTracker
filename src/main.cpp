#include <Arduino.h>

#include "GY_85.h"

#define GYRO_ALPHA 0.9  // gyro + accel
#define GYRO_BETA 0.9   // gyro + mag

GY_85 gy85;

float prev_time = 0;
double pitch = 0;
double roll = 0;
double yaw = 0;

float yaw_zero = 0, pitch_zero = 0, roll_zero = 0;

float deg2rad(float deg) {
    return deg * PI / 180;
}

float rad2deg(float rad) {
    return rad * 180 / PI;
}

void setup() {
    gy85.init();
    Serial.begin(115200);
}

void loop() {
    // read the accelerometer
    // values are in g
    float ax, ay, az;
    gy85.readAccel(&ax, &ay, &az);

    // read the gyroscope
    // values are in degrees per second
    float gx, gy, gz;
    gy85.readGyro(&gx, &gy, &gz);

    // read the magnetometer
    // values are in gauss
    float mx, my, mz;
    gy85.readMag(&mx, &my, &mz);

    // accelerometer pitch and roll
    // float a_pitch = rad2deg(atan2(ax, az));
    float a_pitch = atan2(-ax, sqrt(ay * ay + az * az));
    float a_roll = atan2(ay, az);
    if (pitch_zero == 0) {
        pitch_zero = a_pitch;
    }
    if (roll_zero == 0) {
        roll_zero = a_roll;
    }

    // compensate for tilt
    float comp_x = mx * cos(a_pitch) + mz * sin(a_pitch);
    float comp_y = mx * sin(a_roll) * sin(a_pitch) + my * cos(a_roll) - mz * sin(a_roll) * cos(a_pitch);

    float comp_heading = atan2(comp_y, comp_x);
    if (yaw_zero == 0) {
        yaw_zero = comp_heading;
    }

    // calculate delta time
    float current_time = micros();
    float dt = (current_time - prev_time) / 1000000.0;
    prev_time = current_time;

    // complementary filter
    float gyro_pitch = (pitch + gy * dt);
    float gyro_roll = (roll + gx * dt);
    float gyro_yaw = (yaw + -gz * dt);
    pitch = GYRO_ALPHA * gyro_pitch + (1 - GYRO_ALPHA) * rad2deg(a_pitch - pitch_zero);
    roll = GYRO_ALPHA * gyro_roll + (1 - GYRO_ALPHA) * rad2deg(a_roll - roll_zero);
    yaw = GYRO_BETA * gyro_yaw + (1 - GYRO_BETA) * rad2deg(comp_heading - yaw_zero);

    // Serial.print(">pitch:");
    // Serial.println(pitch);
    // Serial.print(">roll:");
    // Serial.println(roll);
    // Serial.print(">yaw:");
    // Serial.println(yaw);

    Serial.print(roll, 6);
    Serial.print(" ");
    Serial.print(pitch, 6);
    Serial.print(" ");
    Serial.println(yaw, 6);
}