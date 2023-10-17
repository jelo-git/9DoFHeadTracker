#include <Arduino.h>
#include <ADXL345.h>
#include <I2Coms.h>

ADXL345::ADXL345():_I2Coms(0x54){};
ADXL345::~ADXL345(){
    
}