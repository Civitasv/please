#ifndef INCLUDE_PLEASE_TEXT_H_
#define INCLUDE_PLEASE_TEXT_H_
#include "style.h"

namespace please {
class Text {
 public:
  Text() {}
  Text(std::string text) : text_(text) {}
  Text(std::string text, Style style) : text_(text), style_(style) {}

  Text& style(Style style) {
    style_ = style;
    return *this;
  }

  Text& text(std::string text) {
    text_ = text;
    return *this;
  }

  std::string text() { return text_; }

  friend std::ostream& operator<<(std::ostream& os, Text& val) {
    os << val.style_ << val.text_ << Decoration::From(Decoration::RESET);
    return os;
  }

 private:
  Style style_;
  std::string text_;
};
}  // namespace please
#endif  // !INCLUDE_PLEASE_TEXT_H_