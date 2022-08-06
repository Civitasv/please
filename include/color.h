#ifndef INCLUDE_PLEASE_COLOR_H_
#define INCLUDE_PLEASE_COLOR_H_
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>

namespace please {
namespace color {
enum class Style {
  RESET = 0,
  BOLD = 1,
  DIM = 2,
  ITALIC = 3,
  UNDERLINE = 4,
  BLINK = 5,
  RBLINK = 6,
  REVERSED = 7,
  CONCEAL = 8,
  CROSSED = 9
};

enum class Fg {
  BLACK = 30,
  RED = 31,
  GREEN = 32,
  YELLOW = 33,
  BLUE = 34,
  PURPLE = 35,
  CYAN = 36,
  WHITE = 37,
};

enum class Bg {
  BLACK = 40,
  RED = 41,
  GREEN = 42,
  YELLOW = 43,
  BLUE = 44,
  PURPLE = 45,
  CYAN = 46,
  WHITE = 47,
};

enum class BrightFg {
  BLACK = 90,
  RED = 91,
  GREEN = 92,
  YELLOW = 93,
  BLUE = 94,
  PURPLE = 95,
  CYAN = 96,
  WHITE = 97,
};

enum class BrightBg {
  BLACK = 100,
  RED = 101,
  GREEN = 102,
  YELLOW = 103,
  BLUE = 104,
  PURPLE = 105,
  CYAN = 106,
  GRAY = 107
};

class RGB {
public:
  RGB(int r, int g, int b) : r(r), g(g), b(b) {}

  int r;
  int g;
  int b;

  friend std::ostream &operator<<(std::ostream &os, const RGB val) {
    os << "\x1b[38;2;" << val.r << ";" << val.g << ";" << val.b << "m";
    return os;
  }
};

template <typename T>
using EnabledType = typename std::enable_if<
    std::is_same<T, Style>::value || std::is_same<T, Fg>::value ||
        std::is_same<T, Bg>::value || std::is_same<T, BrightFg>::value ||
        std::is_same<T, BrightBg>::value,
    std::ostream &>::type;

template <typename T>
inline EnabledType<T> operator<<(std::ostream &os, const T val) {
  os << "\x1b[" << static_cast<int>(val) << "m";
  return os;
}
}; // namespace color

} // namespace please
#endif