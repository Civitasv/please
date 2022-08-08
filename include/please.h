#ifndef INCLUDE_PLEASE_H_
#define INCLUDE_PLEASE_H_

#include <map>
#include <string>

#include "task.h"
#include "text.h"

namespace please {
static std::string CenterText(Text text);

/// CurrentTime
static std::string CurrentTime(const char* format = "%Y-%m-%d");

/// please
void Show(std::vector<Task> tasks, std::map<std::string, Style> styles,
          int type = 0);

void AddTask(Task task);

/// please add

}  // namespace please

#endif