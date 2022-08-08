#include <fcntl.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <vector>

#include "include/color.h"
#include "include/config.h"
#include "include/please.h"
#include "include/table.h"
#include "include/term.h"

void test_style();
void test_please();
void test_term();
void test_unicode();
void test_config();

int main(int argc, const char **argv) {
  test_please();
  // test_style();
  // test_term();
  // test_unicode();
  // test_config();
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

  passwd *pw = getpwuid(getuid());
  std::string path(pw->pw_dir);
  auto data = FromFile(path + "/.config/please/config.json",
                       path + "/.config/please/tasks.json");
  Show(data);
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

void test_config() {
  using namespace please;
  auto data = FromFile("config.json", "tasks.json");
  for (auto &item : data.tasks) {
    std::cout << item;
  }

  // auto tasks = data.first;
  // tasks.push_back(Task({"2"}, {"B task"}, {"Not Done"}));

  // toFile(tasks);
}