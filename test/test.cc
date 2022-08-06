#include "include/color.h"
#include "include/please.h"
#include <iostream>
#include <vector>

int main(int argc, const char **argv) {
  using namespace please::color;

  std::cout << "RGB: " << RGB(1, 2, 3) << "GIVE ME SOMETHING";
  std::cout << Style::REVERSED << Style::ITALIC << Style::BOLD << Fg::CYAN
            << Bg::WHITE << "TEST" << Style::RESET << "NORMAL";

  return 0;
}
