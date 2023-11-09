#ifndef BINARY_CALCULATOR_HPP
#define BINARY_CALCULATOR_HPP

#include <cstddef>
class BinaryCalculator
{
public:
    std::byte IntToByte(int integer);
    int ByteToInt(std::byte byte);
};

#endif