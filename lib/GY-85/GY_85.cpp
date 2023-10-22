#include "GY_85.h"

void GY_85::init()
{
    Wire.begin();
    startAccel();
    startGyro();
    startMag();
}

// accelerometer
void GY_85::startAccel()
{
    // Set the +/- 4g, 10-bit mode
    Wire.beginTransmission(ADXL345);
    Wire.write(0x31); // DATA_FORMAT register
    Wire.write(0x01); // Set to 4g, 10-bit mode
    Wire.endTransmission();
    // Start measurement
    Wire.beginTransmission(ADXL345);
    Wire.write(0x2D); // POWER_CTL register
    Wire.write(8);    // Measurement mode
    Wire.endTransmission();
}
void GY_85::readAccel(int *x, int *y, int *z)
{
    // Read 6 bytes from the ADXL345
    // Each axis reading comes in 10 bit resolution, ie 2 bytes.  Least Significat Byte first!!
    // Thus we are converting both bytes in to one int
    Wire.beginTransmission(ADXL345);
    Wire.write(ADXL345_DATAX0); // Start with register 0x32
    Wire.endTransmission();
    Wire.requestFrom(ADXL345, 6);
    if (Wire.available() <= 6)
    {
        *x = Wire.read() | Wire.read() << 8; // x-axis
        *y = Wire.read() | Wire.read() << 8; // y-axis
        *z = Wire.read() | Wire.read() << 8; // z-axis
    }
}

// gyroscope
void GY_85::startGyro()
{
    Wire.beginTransmission(ITG3200);
    Wire.write(0x3E); // PWR_MGM register
    Wire.write(0x00); // PLL with X gyro reference
    Wire.endTransmission();

    Wire.beginTransmission(ITG3200);
    Wire.write(0x15); // SMPLRT_DIV register
    Wire.write(0x07); // Sample rate = 1kHz/(7+1) = 125Hz
    Wire.endTransmission();

    Wire.beginTransmission(ITG3200);
    Wire.write(0x16); // DLPF_FS register
    Wire.write(0x1E); // Full scale range = 2000 dps
    Wire.endTransmission();

    Wire.beginTransmission(ITG3200);
    Wire.write(0x17); // INT_CFG register
    Wire.write(0x00); // Interrupt generation
    Wire.endTransmission();

    delay(100); // Wait for sensor to stabilize

    calibrateGyro();
}
void GY_85::calibrateGyro()
{
    int x, y, z;
    int xSum = 0, ySum = 0, zSum = 0;
    for (int i = 0; i < 100; i++)
    {
        readGyro(&x, &y, &z);
        xSum += x;
        ySum += y;
        zSum += z;
        delay(10);
    }
    gyroXoffset = xSum / 100;
    gyroYoffset = ySum / 100;
    gyroZoffset = zSum / 100;
}
void GY_85::readGyro(int *x, int *y, int *z)
{
    // Read 6 bytes from the ITG3200
    // Each axis reading comes in 16 bit resolution, ie 2 bytes.  Most Significat Byte first!!
    // Thus we are converting both bytes in to one int
    Wire.beginTransmission(ITG3200);
    Wire.write(ITG3205_GYRO_XOUT_H); // Start with register 0x1D
    Wire.endTransmission();
    Wire.requestFrom(ITG3200, 6);
    if (Wire.available() <= 6)
    {
        *x = (Wire.read() << 8) | Wire.read(); // x-axis
        *y = (Wire.read() << 8) | Wire.read(); // y-axis
        *z = (Wire.read() << 8) | Wire.read(); // z-axis
    }
    *x -= gyroXoffset;
    *y -= gyroYoffset;
    *z -= gyroZoffset;
}

// magnetometer
void GY_85::startMag()
{
    Wire.beginTransmission(HMC5883L);
    Wire.write(0x02); // Mode register
    Wire.write(0x00); // Continuous mode
    Wire.endTransmission();
}
void GY_85::readMag(int *x, int *y, int *z)
{
    // Read 6 bytes from the HMC5883L
    // Each axis reading comes in 16 bit resolution, ie 2 bytes.  Most Significat Byte first!!
    // Thus we are converting both bytes in to one int
    Wire.beginTransmission(HMC5883L);
    Wire.write(HMC5883L_DATA_OUT_X_MSB); // Start with register 0x03
    Wire.endTransmission();
    Wire.requestFrom(HMC5883L, 6);
    if (Wire.available() <= 6)
    {
        *x = (Wire.read() << 8) | Wire.read(); // x-axis
        *y = (Wire.read() << 8) | Wire.read(); // y-axis
        *z = (Wire.read() << 8) | Wire.read(); // z-axis
    }
}