#ifndef GY_85_H
#define GY_85_H

#include "Arduino.h"
#include "Wire.h"

// Address of the sensors
#define ADXL345 0x53  // Accel device address
#define ITG3200 0x68  // Gyro device address
#define HMC5883L 0x1E // Magnet device address

// First data register of each sensor
#define ADXL345_DATAX0 0x32
#define ITG3205_GYRO_XOUT_H 0x1D
#define HMC5883L_DATA_OUT_X_MSB 0x03

class GY_85
{
private:
    void startAccel();
    void startGyro();
    void startMag();

    void calibrateGyro();
    int gyroXoffset, gyroYoffset, gyroZoffset;

public:
    void init();
    void readAccel(float *x, float *y, float *z);
    void readGyro(int *x, int *y, int *z);
    void readMag(int *x, int *y, int *z);
};

#endif // GY_85_H