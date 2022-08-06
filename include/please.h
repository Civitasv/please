#ifndef INCLUDE_PLEASE_H_
#define INCLUDE_PLEASE_H_

#include <string>

namespace please {

/// CurrentTime
static std::string CurrentTime(const char* format = "%Y-%m-%d");

/// please
void Show();

std::string Tasks();

/// please add

}  // namespace please

#endif