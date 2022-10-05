module;

#include <cmath>
#include <type_traits>

export module Utils.Numbers;

// C++20 - requires in template typename definition

export {

  template <typename T>
  concept number = std::is_arithmetic_v<T>;

  template <typename T>
  requires std::is_integral_v<T>
  inline bool is_power_of_two(const T &x) { return x && !(x & (x - 1)); }

  template <typename T>
  requires std::is_floating_point_v<T>
  bool is_power_of_two(const T &x) {
    int exponent;
    const T mantissa = std::frexp(x, &exponent);
    return mantissa == T(0.5) && exponent > 0;
  }

  template <typename T>
  requires(!number<T>) inline bool is_power_of_two(const T &x) { return false; }
}