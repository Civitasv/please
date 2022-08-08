#ifndef INCLUDE_PLEASE_TASK_H_
#define INCLUDE_PLEASE_TASK_H_

#include <string>

#include "text.h"

namespace please {
class Task {
 public:
  Task(std::string task, std::string status) : task_(task), status_(status) {}

  std::string task() const { return task_; };
  std::string status() const { return status_; }

  void status(std::string status) { status_ = status; }

  friend std::ostream& operator<<(std::ostream& os, Task& val) {
    os << val.task_ << " " << val.status_ << '\n';
    return os;
  }

 private:
  std::string task_;
  std::string status_;
};
}  // namespace please
#endif  // !INCLUDE_PLEASE_TASK_H_