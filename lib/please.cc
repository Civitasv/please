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
static std::string CurrentTime(const char* format) {
  std::time_t t = std::time(0);
  char buf[80];
  struct tm time_struct = *localtime(&t);
  strftime(buf, sizeof(buf), format, &time_struct);
  return buf;
}

void Show() {
  using namespace style;
  auto date_now = CurrentTime();
  auto user_name = "Civitasv";

  std::cout << Background(Color::BLUE) << "Hello " << user_name << "! "
            << "It's " << date_now << '\n'
            << Background(Color::RESET);

  std::cout << Tasks() << '\n';
}

std::string Tasks() {
  using namespace style;
  std::stringstream out;
  auto table = Table<style::Color>("tasks");
  table.AddTask(Task("A task"));
  table.AddTask(Task("B task"));
  table.AddTask(Task("C task"));
  table.AddTask(Task("D task"));

  for (auto& task : table.tasks()) {
    if (task.status() == TaskStatus::DONE) {
      out << Foreground(Color::GREEN) << task.task()
          << " ❤️ ↑ \u2654\n"
          << Foreground(Color::RESET);
    } else {
      out << Foreground(Color::RED) << task.task()
          << Foreground(Color::RESET) << " DONE\n";
    }
  }
  return out.str();
}
}  // namespace please