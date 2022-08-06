#include <fcntl.h>
#include <io.h>
#include <stdio.h>

#include <iostream>
#include <vector>

#include "../include/color.h"
#include "../include/please.h"

void test_style();
void test_please();

int main(int argc, const char **argv) {
  test_please();
  return 0;
}

void test_style() {
  using namespace please::style;
  std::cout << "RGB: " << RGB(1, 2, 3) << "GIVE ME SOMETHING";
  std::cout << Decoration::REVERSED << Decoration::ITALIC << Decoration::BOLD
            << Color::FG_CYAN << Color::BG_WHITE << "TEST" << Reset::RESET_ALL
            << "NORMAL";
}

void test_please() {
  using namespace please;
  Show();
}