#include "../include/please.h"

#include <chrono>
#include <ctime>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "../include/color.h"
#include "../include/table.h"
#include "../include/task.h"

namespace please {
static std::string CenterText(Text text) {
  std::stringstream ss;
  // 1. get text
  std::string str = text.text();
  // get size
  size_t size = str.size();
  // get terminal size
  auto term_size = TermSize();
  size_t width = term_size.second;
  size_t height = term_size.first;

  // whitespace
  size_t whitespaces = (width - size) / 2;
  for (int i = 0; i < whitespaces; i++) {
    ss << " ";
  }
  ss << text;
  for (int i = 0; i < whitespaces; i++) {
    ss << " ";
  }
  ss << '\n';
  return ss.str();
}

static std::string CurrentTime(const char* format) {
  std::time_t t = std::time(0);
  char buf[80];
  struct tm time_struct = *localtime(&t);
  strftime(buf, sizeof(buf), format, &time_struct);
  return buf;
}

void Show() {
  auto date_now = CurrentTime();
  auto user_name = "Civitasv";
  std::stringstream header_str;

  header_str << "Hello " << user_name << "! "
             << "It's " << date_now;
  auto header = Text()
                    .text(header_str.str())
                    .style(Style().fg(Foreground::From(Color::WHITE)));

  std::cout << CenterText(header);

  Tasks();
}

void Tasks() {
  std::stringstream out;
  auto header_style = Style().fg(Foreground::From(Color::GREY));

  // auto table = Table().title("TASKS");
  // table.AddTask(Task("A task", "NOT DONE"));
  // table.AddTask(Task("B task"));
  // table.AddTask(Task("C task"));
  // table.AddTask(Task("D task"));

  // std::cout << table;
}
}  // namespace please