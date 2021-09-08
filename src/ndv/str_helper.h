#pragma once

#include <string>

namespace ndv
{
  template <typename ...Args>
  std::string string_format(const std::string& fmt, Args && ...args)
  {
    int size = std::snprintf(nullptr, 0, fmt.c_str(), std::forward<Args>(args)...);
    std::string output(size + 1, '\0');
    std::sprintf(&output[0], fmt.c_str(), std::forward<Args>(args)...);
    return output;
  }
}