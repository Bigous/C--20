#include <utility>
#include <memory_resource>

export module Utils.Pmr;

export {

template <typename Container, typename... Values>
auto create_container(std::pmr::memory_resource *resource, Values&&... values) {
  Container result{resource};
  result.reserve(sizeof...(values));
  (result.emplace_back(std::forward<Values>(values)),...);
  return result;
}

}