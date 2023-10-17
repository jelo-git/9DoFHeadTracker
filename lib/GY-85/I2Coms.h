#include <Arduino.h>

/// @brief Used as a helper for data transmition between arduino and sensor board
class I2Coms
{
private:
    byte _I2CAddress;
public:
    I2Coms(byte address);
    void WriteToRegister(byte address, byte value);
    void ReadFromRegister(byte address, byte noBytes, byte _buffer[]);
};