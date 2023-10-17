#include <Arduino.h>
#include <I2Coms.h>

class ADXL345
{
private:
    I2Coms _I2Coms;
    void readRawData();
public:
    ADXL345();
    ~ADXL345();
    void readData();
};