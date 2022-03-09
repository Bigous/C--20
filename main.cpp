#include <string>
#include <vector>

#include <iomanip>
#include <iostream>

#include <ranges>

#include <typeinfo>

// import std.core; // needs /MD /EHsc /std:c++latest /experimental:module ...

import Utils.Numbers;
import helloworld;
import Utils.Generators;

auto bool_to_string = [](const bool& b) { return b ? "true" : "false"; };

template <typename T>
requires number<T>
void print_power_of_two(const std::vector<T> &values) {

    for (const auto& value : values) {
        std::cout << "is_power_of_two(" << value
                  << ") : where the value is of type " << typeid(value).name()
                  << " = " << bool_to_string(is_power_of_two(value))
                  << std::endl;
    }
}

int main(int, char **) {
    using namespace std::ranges;

    hello();

    auto fibonacci = utils::generators::fibonacci();

    for (int i = 0; i < 10; ++i) {
        std::cout << "Fibonacci(" << i << ") = " << fibonacci() << std::endl;
    }

    // Not working...
    // auto count { utils::generators::co_counter(10) };
    // for( const auto & val: count) {
    //     std::cout << "Counter = " << val << std::endl;
    //     if( val > 20 )
    //         break;
    // }

    std::vector<int> ints = {1, 8, 39, 128, 127};
    std::vector<float> floats = {1.0, 8.0, 39.0, 128.0, 127.0, 128.5};

    std::cout << std::fixed << std::setw(3) << std::setprecision(1);

    print_power_of_two(ints);
    print_power_of_two(floats);

    auto result{
        ints |
        views::filter([](const auto &value) { return is_power_of_two(value); }) |
        views::transform([](const auto &value) { return std::to_string(value); })
    };

    for (auto i : result) {
        std::cout << i << std::endl;
    }

    return 0;
}
