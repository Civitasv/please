#ifndef INCLUDE_PLEASE_H_
#define INCLUDE_PLEASE_H_

#include <string>
#include "text.h"

namespace please {
static std::string CenterText(Text text);

/// CurrentTime
static std::string CurrentTime(const char* format = "%Y-%m-%d");

/// please
void Show();

void Tasks();

/// please add

}  // namespace please

#endif