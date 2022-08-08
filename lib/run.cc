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

  if (argc == 1) {
    Show(data);
    return 0;
  }

  std::string command = argv[1];
  if (command == "show") {
    if (argc == 2) {
      Show(data);
    } else if (argc == 3) {
      std::string next = argv[2];
      if (next == "all") {
        Show(data);
      } else if (next == "done") {
        Show(data, 1);
      } else if (next == "undone") {
        Show(data, 2);
      }
    } else {
      std::cerr << "Invalid parameters" << std::endl;
    }
  } else if (command == "add") {
    if (argc == 3) {
      std::string item = argv[2];
      auto style = data.style["TASK-NOT DONE"];
      data.tasks.push_back(Task(item, "NOT DONE"));
      Show(data);

      toFile(data.tasks, tasks_path);
    } else {
      std::cerr << "Invalid parameters" << std::endl;
    }
  } else if (command == "done") {
    if (argc == 3) {
      size_t index = std::stoi(argv[2]);
      data.tasks[index - 1].status("DONE");
      Show(data);

      toFile(data.tasks, tasks_path);
    } else {
      std::cerr << "Invalid parameters" << std::endl;
    }
  } else if (command == "undone") {
    if (argc == 3) {
      size_t index = std::stoi(argv[2]);
      data.tasks[index - 1].status("NOT DONE");
      Show(data);

      toFile(data.tasks, tasks_path);
    } else {
      std::cerr << "Invalid parameters" << std::endl;
    }
  } else if (command == "delete") {
    if (argc == 3) {
      size_t index = std::stoi(argv[2]);
      data.tasks.erase(data.tasks.begin() + index - 1);
      Show(data);

      toFile(data.tasks, tasks_path);
    } else {
      std::cerr << "Invalid parameters" << std::endl;
    }
  } else {
    std::cerr << "Invalid parameters" << std::endl;
  }
}