#include <Arduino.h>
#include <I2Coms.h>

#ifndef ADXL345_h
#define ADXL345_h
class ADXL345
{
private:
    I2Coms _I2Coms;
    void readRawData(short int *_rawData);

public:
    ADXL345();
    void readData(float *_data);
};
#endif