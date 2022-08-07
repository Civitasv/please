#include <fcntl.h>
#include <stdio.h>

#include <iostream>
#include <vector>

#include "include/color.h"
#include "include/please.h"
#include "include/table.h"
#include "include/term.h"

void test_style();
void test_please();
void test_term();
void test_unicode();

int main(int argc, const char **argv) {
  test_please();
  // test_style();
  // test_term();
  // test_unicode();
  return 0;
}

void test_style() {
  using namespace please;
  std::cout << "RGB: " << Foreground::From(RGB(1, 2, 3)) << "GIVE ME SOMETHING"
            << Foreground::From(Color::RESET) << '\n';
  std::cout << "Normal" << '\n';

  std::cout << Decoration::From(Decoration::RESET) << "┳Bold" << '\n';
}

void test_please() {
  using namespace please;
  Show();
}

void test_term() {
  using namespace please;
  std::cout << "Terminal size: " << TermSize().first << " ; "
            << TermSize().second << '\n';
}

void test_unicode() {
  std::string a = "👍";
  std::cout << a;
}