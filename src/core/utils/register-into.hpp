
#pragma once

#include <vector>
#include <memory>

namespace Core::Utils {

template <typename T>
T* RegisterInto(std::vector<std::unique_ptr<T>>& container, std::unique_ptr<T> item)
{
  item->OnRegistration();
  container.push_back(std::move(item));
  return container.back().get();
};

}  // namespace Core::Utils
