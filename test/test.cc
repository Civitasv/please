#include <fcntl.h>
#include <stdio.h>

#include <iostream>
#include <vector>

#include "include/color.h"
#include "include/please.h"

void test_style();
void test_please();

int main(int argc, const char **argv) {
  // test_please();
  test_style();
  return 0;
}

void test_style() {
  using namespace please::style;
  std::cout << "RGB: " << Foreground(RGB(1, 2, 3)) << "GIVE ME SOMETHING"
            << Foreground(Color::RESET) << '\n';
  std::cout << "Normal" << '\n';

  std::cout << Decoration(Attribute::BOLD) << "Bold" << '\n';
}

void test_please() {
  using namespace please;
  Show();
}