#ifndef INCLUDE_PLEASE_TASK_H_
#define INCLUDE_PLEASE_TASK_H_

#include <string>

namespace please {
enum class TaskStatus { DONE, START };

class Task {
 public:
  Task(std::string task, TaskStatus status = TaskStatus::DONE)
      : task_(task), status_(status) {}

  std::string task() const {return task_;};
  TaskStatus status() const { return status_; }

 private:
  std::string task_;
  TaskStatus status_;
};
}  // namespace please
#endif  // !INCLUDE_PLEASE_TASK_H_