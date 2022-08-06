#ifndef INCLUDE_PLEASE_COLOR_H_
#define INCLUDE_PLEASE_COLOR_H_

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

/// for detailed info, refered to
/// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797.
namespace please {
namespace style {
enum class Reset {
  RESET_ALL = 0,
  RESET_BOLD = 22,
  RESET_DIM = 22,
  RESET_ITALIC = 23,
  RESET_UNDERLINE = 24,
  RESET_BLINK = 25,
  RESET_REVERSED = 27,
  RESET_CONCEAL = 28,
  RESET_CROSSED = 29,
  RESET_FG = 39,
  RESET_BG = 49
};

enum class Decoration {
  BOLD = 1,
  DIM = 2,
  ITALIC = 3,
  UNDERLINE = 4,
  BLINK = 5,
  REVERSED = 7,
  CONCEAL = 8,
  CROSSED = 9
};

enum class Color {
  FG_BLACK = 30,
  FG_RED = 31,
  FG_GREEN = 32,
  FG_YELLOW = 33,
  FG_BLUE = 34,
  FG_PURPLE = 35,
  FG_CYAN = 36,
  FG_WHITE = 37,

  BG_BLACK = 40,
  BG_RED = 41,
  BG_GREEN = 42,
  BG_YELLOW = 43,
  BG_BLUE = 44,
  BG_PURPLE = 45,
  BG_CYAN = 46,
  BG_WHITE = 47,

  BRIGHT_FG_BLACK = 90,
  BRIGHT_FG_RED = 91,
  BRIGHT_FG_GREEN = 92,
  BRIGHT_FG_YELLOW = 93,
  BRIGHT_FG_BLUE = 94,
  BRIGHT_FG_PURPLE = 95,
  BRIGHT_FG_CYAN = 96,
  BRIGHT_FG_WHITE = 97,

  BRIGHT_BG_BLACK = 100,
  BRIGHT_BG_RED = 101,
  BRIGHT_BG_GREEN = 102,
  BRIGHT_BG_YELLOW = 103,
  BRIGHT_BG_BLUE = 104,
  BRIGHT_BG_PURPLE = 105,
  BRIGHT_BG_CYAN = 106,
  BRIGHT_BG_GRAY = 107
};

class Color256 {
 public:
  Color256(int id, bool fg = true) : id(id), fg(fg) {}

  int id;
  bool fg;

  friend std::ostream &operator<<(std::ostream &os, const Color256 val) {
    os << "\x1b[" << (val.fg ? 38 : 48) << ";5;" << val.id << "m";
    return os;
  }
};

class RGB {
 public:
  RGB(int r, int g, int b, bool fg = true) : r(r), g(g), b(b), fg(fg) {}

  int r;
  int g;
  int b;
  bool fg;

  friend std::ostream &operator<<(std::ostream &os, const RGB val) {
    os << "\x1b[" << (val.fg ? 38 : 48) << ";2;" << val.r << ";" << val.g << ";"
       << val.b << "m";
    return os;
  }
};

template <typename T>
class Style {
  static_assert(std::is_same<T, Color>::value ||
                    std::is_same<T, Color256>::value ||
                    std::is_same<T, RGB>::value,
                "T must be Color");

 public:
  Style(std::vector<Decoration> decorations = {}, T color = Color::FG_WHITE)
      : decorations_(decorations), color_(color) {}

 private:
  std::vector<Decoration> decorations_;
  T color_;
};

template <typename T>
using EnabledType =
    typename std::enable_if<std::is_same<T, Decoration>::value ||
                                std::is_same<T, Reset>::value ||
                                std::is_same<T, Color>::value,
                            std::ostream &>::type;

template <typename T>
inline EnabledType<T> operator<<(std::ostream &os, const T val) {
  os << "\x1b[" << static_cast<int>(val) << "m";
  return os;
}
};  // namespace style

}  // namespace please
#endif