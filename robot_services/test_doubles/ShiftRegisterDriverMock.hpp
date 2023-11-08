#ifndef SHIFT_REGISTER_DRIVER_MOCK_HPP
#define SHIFT_REGISTER_DRIVER_MOCK_HPP

#include "robot_interfaces/ShiftRegisterDriver.hpp"
#include "gmock/gmock.h"
#include <bitset>

class ShiftRegisterDriverMock
: public ShiftRegisterDriver
{
    public:
        MOCK_METHOD(void, EnableOutput, ());
        MOCK_METHOD(void, DisableOutput, ());
        MOCK_METHOD(void, ShiftByte, (std::bitset<8> byte));
        MOCK_METHOD(void, ShiftBit, (bool bit));



};

#endif 