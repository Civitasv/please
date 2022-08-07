#ifndef INCLUDE_PLEASE_TASK_H_
#define INCLUDE_PLEASE_TASK_H_

#include <string>
#include "text.h"

namespace please {
class Task {
 public:
  Task(Text task, std::string status = "DONE") : task_(task), status_(status) {}

  Text task() const { return task_; };
  std::string status() const { return status_; }

 private:
  Text task_;
  std::string status_;
};
}  // namespace please
#endif  // !INCLUDE_PLEASE_TASK_H_