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

int main(int argc, const char **argv) {
  test_please();
  // test_style();
  // test_term();
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
  // Show();
  Table table = {{{"Country"}, {"Capital"}, {"Population"},
                  {"Area"}, {"Currency"}}};
  table.SetPadding(1);
  table.SetLineSymbol(1);

  table += {{"Germany",Style().fg(Foreground::From(Color::CYAN))},
            {"Berlin"}, {"82,800,000"}, {"357,168 km2"}, {"Euro"}};
  // table.Sort(true);

  std::cout << table;
}

void test_term() {
  using namespace please;
  std::cout << "Terminal size: " << TermSize().first << " ; "
            << TermSize().second << '\n';
}