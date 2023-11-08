#ifndef ROBOT_INTERFACES_SHIFT_REGISTER_DRIVER_HPP
#define ROBOT_INTERFACES_SHIFT_REGISTER_DRIVER_HPP

#include <bitset>
#include <cstdint>

class ShiftRegisterDriver
{
public:
    virtual void EnableOutput() = 0;
    virtual void DisableOutput() = 0;
    virtual void ShiftByte(std::bitset<8> byte) = 0;
    virtual void ShiftBit(bool bit) = 0;
};

#endif
