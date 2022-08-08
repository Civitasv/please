#ifndef INCLUDE_PLEASE_TASK_H_
#define INCLUDE_PLEASE_TASK_H_

#include <string>

#include "text.h"

namespace please {
class Task {
 public:
  Task(size_t id, std::string task, std::string status)
      : id_(id), task_(task), status_(status) {}

  size_t id() const { return id_; };
  std::string task() const { return task_; };
  std::string status() const { return status_; }

  void status(std::string status) { status_ = status; }

  friend std::ostream& operator<<(std::ostream& os, Task& val) {
    os << val.id_ << " " << val.task_ << " " << val.status_ << '\n';
    return os;
  }

 private:
  size_t id_;
  std::string task_;
  std::string status_;
};
}  // namespace please
#endif  // !INCLUDE_PLEASE_TASK_H_