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
  struct tm time_struct;
  localtime_s(&time_struct, &t);
  strftime(buf, sizeof(buf), format, &time_struct);
  return buf;
}

void Show() {
  auto date_now = CurrentTime();
  auto user_name = "Civitasv";

  std::cout << style::Color::FG_CYAN << "Hello " << user_name << "! "
            << "It's " << date_now << '\n'
            << style::Reset::RESET_ALL;

  std::cout << Tasks() << '\n';
}

std::string Tasks() {
  std::stringstream out;
  auto table = Table<style::Color>("tasks");
  table.AddTask(Task("A task"));
  table.AddTask(Task("B task"));
  table.AddTask(Task("C task"));
  table.AddTask(Task("D task"));

  for (auto& task : table.tasks()) {
    if (task.status() == TaskStatus::DONE) {
      out << style::Color::FG_GREEN << task.task() << style::Reset::RESET_FG << " NOT DONE\n";
    } else {
      out << style::Color::FG_RED << task.task() << style::Reset::RESET_FG << " DONE\n";
    }
  }
  return out.str();
}
}  // namespace please