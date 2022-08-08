#ifndef INCLUDE_PLEASE_CONFIG_H_
#define INCLUDE_PLEASE_CONFIG_H_

#include "include/task.h"
#include "nlohmann/json.hpp"

namespace please {
using json = nlohmann::json;

typedef struct Config {
  std::string name;
  std::map<std::string, Style> style;
  std::vector<Task> tasks;
} Config;

Config FromFile(std::string config_file, std::string tasks_file);

void toFile(std::vector<Task> tasks, std::string tasks_file);

static Style Resolve(json value);
}  // namespace please

#endif  // !INCLUDE_PLEASE_CONFIG_H_