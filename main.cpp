#include <iostream>
#include <vector>
#include <ranges>
#include <string>

//import std.core; // needs /MD /EHsc /std:c++latest /experimental:module ...

import Utils.Numbers;
import helloworld;
import Utils.Generators;

int main(int, char**) { 
    using namespace std::ranges;

    hello();

    auto fibonacci = utils::generators::fibonacci();

    auto bool_to_string = [](bool b) {
        return b ? "true" : "false";
    };

    for( int i = 0; i < 10; ++i ) {
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
    std::vector<float> floats = {1.0, 8.0, 39.0, 128.0, 127.0};

    for(auto i : ints) {
        std::cout << "is_power_of_two(" << i << ") = " << bool_to_string(is_power_of_two(i)) << std::endl;
    }

    for(auto i : floats) {
        std::cout << "is_power_of_two(" << i << ") = " << bool_to_string(is_power_of_two(i)) << std::endl;
    }

    auto result { ints 
        | views::filter([](const auto& value){ return is_power_of_two(value); })
        | views::transform([](const auto& i){return std::to_string(i);})
    };

    for(auto i : result) {
        std::cout << i << std::endl;
    }

    return 0;
}
