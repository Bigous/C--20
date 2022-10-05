module;

#include <experimental/generator>
#include <stdexcept>

export module Utils.Generators;

export {
  namespace utils {
  namespace generators {

  // Lambda mutation is acctually a function call from c++14.
  auto fibonacci() {
    return [i = 1ULL, y = 1ULL]() mutable {
      if (y < i) {
        throw std::runtime_error("fibonacci: last possible iteration reached");
      }
      auto ret = i;
      i = y;
      y += ret;
      return ret;
    };
  }

  // Lambda mutation is acctually a function call from c++14.
  auto counter(int start = 0) {
    return [i = start]() mutable { return i++; };
  }

  std::experimental::generator<int> co_counter(const int &start = 0) {
    int c{start};
    while (true)
      co_yield c++;
  }

  } // namespace generators
  } // namespace utils
}