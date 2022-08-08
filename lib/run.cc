#include <pwd.h>
#include <unistd.h>

#include "include/config.h"
#include "include/please.h"

int main(int argc, char* argv[]) {
  using namespace please;

  // 1. get styles and tasks
  passwd* pw = getpwuid(getuid());
  std::string path(pw->pw_dir);
  auto config_path = path + "/.config/please/config.json";
  auto tasks_path = path + "/.config/please/tasks.json";
  auto data = FromFile(config_path, tasks_path);

  auto tasks = data.first;
  auto styles = data.second;
  if (argc == 1) {
    Show(tasks, styles);
    return 0;
  }
  std::string command = argv[1];
  if (command == "show") {
    if (argc == 3) {
      std::string next = argv[2];
      if (next == "all") {
        Show(tasks, styles);
      } else if (next == "done") {
        Show(tasks, styles, 1);
      } else if (next == "undone") {
        Show(tasks, styles, 2);
      }
    } else {
      Show(tasks, styles);
    }
  } else if (command == "add") {
    std::string item = argv[2];
    auto style = styles["TASK-NOT DONE"];
    tasks.push_back(Task(tasks.size() + 1, item, "NOT DONE"));
    Show(tasks, styles);

    toFile(tasks, tasks_path);
  } else if (command == "done") {
    size_t index = std::stoi(argv[2]);
    tasks[index - 1].status("DONE");
    Show(tasks, styles);

    toFile(tasks, tasks_path);
  } else if (command == "undone") {
    size_t index = std::stoi(argv[2]);
    tasks[index - 1].status("UNDONE");
    Show(tasks, styles);

    toFile(tasks, tasks_path);
  } else if (command == "delete") {
    size_t index = std::stoi(argv[2]);
    tasks.erase(tasks.begin() + index - 1);
    Show(tasks, styles);

    toFile(tasks, tasks_path);
  }
}