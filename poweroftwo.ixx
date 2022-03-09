module;

#include <type_traits>
#include <cmath>

export module Utils.Numbers;

// C++20 - requires in template typename definition

export {

template<typename T>
concept number = std::is_integral_v<T> || std::is_floating_point_v<T>;

template<typename T> requires std::is_integral_v<T>
bool is_power_of_two(const T& x) {
    return x && !(x & (x - 1));
}

template<typename T> requires std::is_floating_point_v<T>
bool is_power_of_two(const T &x) {
    int exponent;
    const T mantissa = std::frexp(x, &exponent);
    return mantissa == T(0.5) && exponent > 0;
}

}