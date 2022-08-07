#ifndef INCLUDE_PLEASE_COLOR_H_
#define INCLUDE_PLEASE_COLOR_H_

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

/// for detailed info, refered to
/// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797.
/// https://talyian.github.io/ansicolors/
namespace please {
namespace style {
enum class Attribute {
  RESET = 0,
  BOLD = 1,
  DIM = 2,
  ITALIC = 3,
  UNDERLINE = 4,
  SLOWBLINK = 5,
  RAPIDBLINK = 6,
  REVERSED = 7,
  CONCEAL = 8,
  CROSSED = 9,

  NO_BOLD = 22,
  NO_DIM = 22,
  NO_ITALIC = 23,
  NO_UNDERLINE = 24,
  NO_BLINK = 25,
  NO_REVERSED = 27,
  NO_CONCEAL = 28,
  NO_CROSSED = 29
};

enum class Color {
  BLACK = 0,
  DARK_GREY = 8,
  RED = 9,
  DARK_RED = 1,
  GREEN = 10,
  DARK_GREEN = 2,
  YELLOW = 11,
  DARK_YELLOW = 3,
  BLUE = 12,
  DARK_BLUE = 4,
  PURPLE = 13,
  DARK_PURPLE = 5,
  CYAN = 14,
  DARK_CYAN = 6,
  WHITE = 15,
  GREY = 7,

  RESET,
};

class Color256 {
 public:
  Color256(int id) : id(id) {}

  int id;
};

class RGB {
 public:
  RGB(int r, int g, int b) : r(r), g(g), b(b) {}

  int r;
  int g;
  int b;
};

inline std::string Background(Color color) {
  if (color == Color::RESET) {
    return "\x1b[49m";
  }
  std::stringstream os;
  os << "\x1b[48;5;" << static_cast<int>(color) << "m";
  return os.str();
}

inline std::string Background(RGB color) {
  std::stringstream os;
  os << "\x1b[48;2;" << color.r << ";" << color.g << ";" << color.b << "m";
  return os.str();
}

inline std::string Background(Color256 color) {
  std::stringstream os;
  os << "\x1b[48;5;" << color.id << "m";
  return os.str();
}

inline std::string Foreground(Color color) {
  if (color == Color::RESET) {
    return "\x1b[39m";
  }
  std::stringstream os;
  os << "\x1b[38;5;" << static_cast<int>(color) << "m";
  return os.str();
}

inline std::string Foreground(RGB color) {
  std::stringstream os;
  os << "\x1b[38;2;" << color.r << ";" << color.g << ";" << color.b << "m";
  return os.str();
}

inline std::string Foreground(Color256 color) {
  std::stringstream os;
  os << "\x1b[38;5;" << color.id << "m";
  return os.str();
}

class Decoration {
 public:
  Decoration(Attribute attr) : attr_(attr) {}

  friend std::ostream& operator<<(std::ostream& os, const Decoration& val) {
    os << "\x1b[" << static_cast<int>(val.attr_) << "m";
    return os;
  }

 private:
  Attribute attr_;
};
}  // namespace style
}  // namespace please
#endif