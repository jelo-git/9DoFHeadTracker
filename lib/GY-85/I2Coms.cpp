#include <Arduino.h>
#include <Wire.h>
#include <I2Coms.h>

/// @brief Begin I2C communication
/// @param address of device
I2Coms::I2Coms(byte address)
{
    Wire.begin();
    _I2CAddress = address;
}
/// @brief Write data to register throught I2C
/// @param address aka "where" 
/// @param value aka "what"
void I2Coms::WriteToRegister(byte address, byte value){
    Wire.beginTransmission(_I2CAddress);
    Wire.write(address);    //where
    Wire.write(value);      //what
    Wire.endTransmission();
    return;
}
/// @brief Read fata from register throught I2C
/// @param address starting address of data read
/// @param noBytes amount of data to read
/// @param _buffer place where data will be stored
void I2Coms::ReadFromRegister(byte address, byte noBytes, byte _buffer[]){
    // Where to listen
    Wire.beginTransmission(_I2CAddress);
    Wire.write(address);
    Wire.endTransmission();

    // Listen to data
    Wire.beginTransmission(_I2CAddress);
    Wire.requestFrom(_I2CAddress,noBytes);
    int n = 0;
    while (Wire.available())
    {
        _buffer[n] = Wire.read();
        n++;
    }
    Wire.endTransmission();
    return;
}