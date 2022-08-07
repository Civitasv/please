#ifndef INCLUDE_PLEASE_TERM_H_
#define INCLUDE_PLEASE_TERM_H_
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdio>

namespace please {
inline std::pair<size_t,size_t> TermSize() {
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  return {static_cast<size_t>(size.ws_row), static_cast<size_t>(size.ws_col)};
}
}  // namespace please
#endif  // !INCLUDE_PLEASE_TERM_H_