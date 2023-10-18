#include <Arduino.h>

/// @brief Used as a helper for data transmition between arduino and sensor board
#ifndef I2Coms_h
#define I2Coms_h
class I2Coms
{
private:
    byte _I2CAddress;

public:
    I2Coms(byte address);
    void writeToRegister(byte address, byte value);
    void readFromRegister(byte address, byte noBytes, byte _buffer[]);
};
#endif