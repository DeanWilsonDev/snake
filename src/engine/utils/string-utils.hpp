#pragma once

namespace Engine {
namespace StringUtils {
static char* DuplicateAsCString(const std::string& source)
{
#if defined(_WIN32)
  return _strdup(source.c_str());
#else
  return strdup(source.c_str());
#endif
}
}  // namespace StringUtils

}  // namespace Engine
