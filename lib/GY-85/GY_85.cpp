#include "GY_85.h"

void GY_85::init(AccelScale ascale, MagScale mscale) {
    Wire.begin();
    accelScale = ascale;
    magScale = mscale;
    gyroCalibrated = false;
    startAccel();
    startGyro();
    startMag();
}

// accelerometer
void GY_85::startAccel() {
    // Set the +/- 4g, 10-bit mode
    Wire.beginTransmission(ADXL345);
    Wire.write(0x31);  // DATA_FORMAT register
    Wire.write(accelScale);
    Wire.endTransmission();
    // Start measurement
    Wire.beginTransmission(ADXL345);
    Wire.write(0x2D);  // POWER_CTL register
    Wire.write(8);     // Measurement mode
    Wire.endTransmission();
}
void GY_85::readAccel(float *x, float *y, float *z) {
    // Read 6 bytes from the ADXL345
    // Each axis reading comes in 10 bit resolution, ie 2 bytes.  Least Significat Byte first!!
    // Thus we are converting both bytes in to one int
    Wire.beginTransmission(ADXL345);
    Wire.write(ADXL345_DATAX0);  // Start with register 0x32
    Wire.endTransmission();
    Wire.requestFrom(ADXL345, 6);
    if (Wire.available() <= 6) {
        *x = Wire.read() | Wire.read() << 8;  // x-axis
        *y = Wire.read() | Wire.read() << 8;  // y-axis
        *z = Wire.read() | Wire.read() << 8;  // z-axis
    }

    // Convert to g's
    switch (accelScale) {
        case A_2G:
            *x *= 3.9 / 1000;
            *y *= 3.9 / 1000;
            *z *= 3.9 / 1000;
            break;
        case A_4G:
            *x *= 7.8 / 1000;
            *y *= 7.8 / 1000;
            *z *= 7.8 / 1000;
            break;
        case A_8G:
            *x *= 15.6 / 1000;
            *y *= 15.6 / 1000;
            *z *= 15.6 / 1000;
            break;
        case A_16G:
            *x *= 31.2 / 1000;
            *y *= 31.2 / 1000;
            *z *= 31.2 / 1000;
            break;
    }
}

// gyroscope
void GY_85::startGyro() {
    Wire.beginTransmission(ITG3200);
    Wire.write(0x3E);  // PWR_MGM register
    Wire.write(0x00);  // PLL with X gyro reference
    Wire.endTransmission();

    Wire.beginTransmission(ITG3200);
    Wire.write(0x15);  // SMPLRT_DIV register
    Wire.write(0x07);  // Sample rate = 1kHz/(7+1) = 125Hz
    Wire.endTransmission();

    Wire.beginTransmission(ITG3200);
    Wire.write(0x16);  // DLPF_FS register
    Wire.write(0x1E);  // Full scale range = 2000 dps
    Wire.endTransmission();

    Wire.beginTransmission(ITG3200);
    Wire.write(0x17);  // INT_CFG register
    Wire.write(0x00);  // Interrupt generation
    Wire.endTransmission();

    delay(100);  // Wait for sensor to stabilize

    // calibrateGyro();
}
void GY_85::calibrateGyro() {
    float x, y, z;
    float xSum = 0, ySum = 0, zSum = 0;
    for (int i = 0; i < 100; i++) {
        readGyro(&x, &y, &z);
        xSum += x;
        ySum += y;
        zSum += z;
        delay(10);
    }
    gyroXoffset = xSum / 100;
    gyroYoffset = ySum / 100;
    gyroZoffset = zSum / 100;
    gyroCalibrated = true;
}
void GY_85::readGyro(float *x, float *y, float *z) {
    // Read 6 bytes from the ITG3200
    // Each axis reading comes in 16 bit resolution, ie 2 bytes.  Most Significat Byte first!!
    // Thus we are converting both bytes in to one int
    Wire.beginTransmission(ITG3200);
    Wire.write(ITG3205_GYRO_XOUT_H);  // Start with register 0x1D
    Wire.endTransmission();
    Wire.requestFrom(ITG3200, 6);
    if (Wire.available() <= 6) {
        *x = (Wire.read() << 8) | Wire.read();  // x-axis
        *y = (Wire.read() << 8) | Wire.read();  // y-axis
        *z = (Wire.read() << 8) | Wire.read();  // z-axis
    }

    // Convert to degrees per second -> 14.375 LSBs per degrees/sec
    *x /= 14.375;
    *y /= 14.375;
    *z /= 14.375;

    if (gyroCalibrated) {
        *x -= gyroXoffset;
        *y -= gyroYoffset;
        *z -= gyroZoffset;
    }
}

// magnetometer
void GY_85::startMag() {
    Wire.beginTransmission(HMC5883L);
    Wire.write(0x00);  // Configuration register A
    Wire.write(0x18);  // 75Hz, normal measurement
    Wire.endTransmission();

    Wire.beginTransmission(HMC5883L);
    Wire.write(0x01);           // Configuration register B
    Wire.write(magScale << 5);  // Set scale
    Wire.endTransmission();

    Wire.beginTransmission(HMC5883L);
    Wire.write(0x02);  // Mode register
    Wire.write(0x00);  // Continuous mode
    Wire.endTransmission();

    delay(100);
}
void GY_85::readMag(float *x, float *y, float *z) {
    // Read 6 bytes from the HMC5883L
    // Each axis reading comes in 16 bit resolution, ie 2 bytes.  Most Significat Byte first!!
    // Thus we are converting both bytes in to one int
    Wire.beginTransmission(HMC5883L);
    Wire.write(HMC5883L_DATA_OUT_X_MSB);  // Start with register 0x03
    Wire.endTransmission();
    Wire.requestFrom(HMC5883L, 6);
    if (Wire.available() <= 6) {
        *x = (Wire.read() << 8) | Wire.read();  // x-axis
        *z = (Wire.read() << 8) | Wire.read();  // z-axis
        *y = (Wire.read() << 8) | Wire.read();  // y-axis
    }

    // Convert to Gauss
    switch (magScale) {
        case M_0_88Ga:
            *x /= 1370;
            *y /= 1370;
            *z /= 1370;
            break;
        case M_1_3Ga:
            *x /= 1090;
            *y /= 1090;
            *z /= 1090;
            break;
        case M_1_9Ga:
            *x /= 820;
            *y /= 820;
            *z /= 820;
            break;
        case M_2_5Ga:
            *x /= 660;
            *y /= 660;
            *z /= 660;
            break;
        case M_4_0Ga:
            *x /= 440;
            *y /= 440;
            *z /= 440;
            break;
        case M_4_7Ga:
            *x /= 390;
            *y /= 390;
            *z /= 390;
            break;
        case M_5_6Ga:
            *x /= 330;
            *y /= 330;
            *z /= 330;
            break;
        case M_8_1Ga:
            *x /= 230;
            *y /= 230;
            *z /= 230;
            break;
    }
}