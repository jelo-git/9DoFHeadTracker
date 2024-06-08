#ifndef GY_85_H
#define GY_85_H

#include "Arduino.h"
#include "Wire.h"

// Address of the sensors
#define ADXL345 0x53   // Accel device address
#define ITG3200 0x68   // Gyro device address
#define HMC5883L 0x1E  // Magnet device address

// First data register of each sensor
#define ADXL345_DATAX0 0x32
#define ITG3205_GYRO_XOUT_H 0x1D
#define HMC5883L_DATA_OUT_X_MSB 0x03

class GY_85 {
   public:
    enum AccelScale {
        A_2G = 0,
        A_4G = 1,
        A_8G = 2,
        A_16G = 3
    };
    enum MagScale {
        M_0_88Ga = 0,
        M_1_3Ga = 1,
        M_1_9Ga = 2,
        M_2_5Ga = 3,
        M_4_0Ga = 4,
        M_4_7Ga = 5,
        M_5_6Ga = 6,
        M_8_1Ga = 7
    };

    void init(AccelScale scale = A_2G, MagScale magScale = M_0_88Ga);
    void readAccel(float *x, float *y, float *z);
    void readGyro(float *x, float *y, float *z);
    void readMag(float *x, float *y, float *z);

   private:
    void startAccel();
    void startGyro();
    void startMag();
    void calibrateGyro();
    float gyroXoffset, gyroYoffset, gyroZoffset;
    AccelScale accelScale;
    MagScale magScale;
    bool gyroCalibrated = false;
};

#endif  // GY_85_H