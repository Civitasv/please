#include "include/please.h"

#include <chrono>
#include <ctime>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "include/color.h"
#include "include/config.h"
#include "include/table.h"
#include "include/task.h"

namespace please {
static std::string CenterText(Text text) {
  std::stringstream ss;
  // 1. get text
  std::string str = text.text();
  // get size
  size_t size = str.length();
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

/// @param type: 0: all, 1: only undone, 2: only done
void Show(std::vector<Task> tasks, std::map<std::string, Style> styles,
          int type) {
  // 1. Print intro
  auto date_now = CurrentTime();
  auto user_name = "Civitasv";
  std::stringstream header_str;

  header_str << "Hello " << user_name << "! "
             << "It's " << date_now;
  auto header = Text().text(header_str.str()).style(styles["intro"]);

  std::cout << '\n' << header << '\n' << '\n';

  // 2. Print table
  Table table = {{Text{"ID", styles["header"]},
                  {Text{"TASK", styles["header"]}},
                  {Text{"STATUS", styles["header"]}}}};

  table.SetPadding(2);
  table.SetLineSymbol(1);

  for (auto& item : tasks) {
    if ((type == 0) || (type == 1 && item.status() == "DONE") ||
        (type == 2 && item.status() == "NOT DONE")) {
      auto style = styles["TASK-" + item.status()];
      table += {{std::to_string(item.id()), style},
                {item.task(), style},
                {item.status(), style}};
    }
  }

  std::cout << table;
}
}  // namespace please
