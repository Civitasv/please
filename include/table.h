#ifndef INCLUDE_PLEASE_TABLE_H_
#define INCLUDE_PLEASE_TABLE_H_
#include <vector>

#include "color.h"
#include "task.h"

namespace please {
template <typename T>
class Table {
 public:
  Table(std::string title, std::vector<Task> tasks = {},
        style::Style<T> title_style = {}, style::Style<T> header_style = {},
        style::Style<T> text_style = {})
      : title_(title),
        tasks_(tasks),
        title_style_(title_style),
        header_style_(header_style),
        text_style_(text_style_) {}

  void AddTask(Task task) { tasks_.push_back(task); }
  std::vector<Task> tasks() { return tasks_; };

 private:
  std::string title_;
  style::Style<T> title_style_;
  style::Style<T> header_style_;
  style::Style<T> text_style_;

  std::vector<Task> tasks_;
};
}  // namespace please
#endif  // !INCLUDE_PLEASE_TABLE_H_