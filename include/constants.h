#ifndef INCLUDE_PLEASE_CONSTANTS_H_
#define INCLUDE_PLEASE_CONSTANTS_H_

#include <limits>

constexpr double kDoubleNotANumber = std::numeric_limits<double>::quiet_NaN();
constexpr double kDoubleInfinity = (std::numeric_limits<double>::infinity)();
constexpr double kDoubleNegInfinity =
    (-(std::numeric_limits<double>::infinity)());

#endif