#ifndef INCLUDE_PLEASE_TASK_H_
#define INCLUDE_PLEASE_TASK_H_

#include <string>

namespace please {
class Task {
 public:
  Task(std::string task, std::string status = "DONE")
      : task_(task), status_(status) {}

  std::string task() const { return task_; };
  std::string status() const { return status_; }

 private:
  std::string task_;
  std::string status_;
};
}  // namespace please
#endif  // !INCLUDE_PLEASE_TASK_H_