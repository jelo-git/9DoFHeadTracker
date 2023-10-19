#include <Arduino.h>
#include <ADXL345.h>
#include <I2Coms.h>

// ADXL345 registers (see ADXL345 data sheet)
#define ADXL345_I2C_ADDRESS 0x53
#define ADXL345_POWER_CTL 0x2D
#define ADXL345_DATA_FORMAT 0x31
#define ADXL345_DATAX0 0x32

// Data format bits (see ADXL345 data sheet)
#define ADXL345_G_RANGE_2 0x00
#define ADXL345_G_RANGE_4 0x01
#define ADXL345_G_RANGE_8 0x02
#define ADXL345_G_RANGE_16 0x03
// Scale factor (see ADXL345 data sheet) for 10-bit readings (2^10 = 1024) and 2g range
#define ADXL345_SCALE_FACTOR (2 * 2) / 1024

ADXL345::ADXL345() : _I2Coms(0x54)
{
    _I2Coms.writeToRegister(ADXL345_POWER_CTL, 0);
    _I2Coms.writeToRegister(ADXL345_POWER_CTL, 16);
    _I2Coms.writeToRegister(ADXL345_POWER_CTL, 8);
    _I2Coms.writeToRegister(ADXL345_DATA_FORMAT, ADXL345_G_RANGE_2);
};

void ADXL345::readRawData(int *_rawData)
{
    byte _buffer[6];
    _I2Coms.readFromRegister(ADXL345_DATAX0, 6, _buffer);
    _rawData[0] = (((int)_buffer[1]) << 8) | _buffer[0];
    _rawData[1] = (((int)_buffer[3]) << 8) | _buffer[2];
    _rawData[2] = (((int)_buffer[5]) << 8) | _buffer[4];
    return;
}

void ADXL345::readData(float *_data)
{
    int _rawData[3];
    readRawData(_rawData);
    _data[0] = (float)_rawData[0] * (float)(4 / 1024);
    _data[1] = (float)_rawData[1] * (float)(4 / 1024);
    _data[2] = (float)_rawData[2] * (float)(4 / 1024);
    return;
}