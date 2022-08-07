#ifndef INCLUDE_PLEASE_TABLE_H_
#define INCLUDE_PLEASE_TABLE_H_
#include <vector>

#include "color.h"
#include "task.h"

namespace please {
template <typename T>
class Style {
 public:
  Style(T fg = style::Color::RESET,
        T bg = style::Color::RESET,
        std::vector<style::Decoration> decorations = {})
      : fg_(fg), bg_(bg), decorations_(decorations) {}

 private:
  T fg_;
  T bg_;
  std::vector<style::Decoration> decorations_;
};

template <typename T>
class Table {
 public:
  Table(std::string title, std::vector<Task> tasks = {},
        Style<T> title_style = {}, Style<T> header_style = {},
        Style<T> text_style = {})
      : title_(title),
        tasks_(tasks),
        title_style_(title_style),
        header_style_(header_style),
        text_style_(text_style) {}

  void AddTask(Task task) { tasks_.push_back(task); }
  std::vector<Task> tasks() { return tasks_; };

 private:
  std::string title_;
  Style<T> title_style_;
  Style<T> header_style_;
  Style<T> text_style_;

  std::vector<Task> tasks_;
};
}  // namespace please
#endif  // !INCLUDE_PLEASE_TABLE_H_