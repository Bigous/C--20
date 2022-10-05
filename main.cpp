#include <array>
#include <execution>
#include <random>
#include <string>
#include <variant>
#include <vector>

#include <iomanip>
#include <iostream>

#include <ranges>

#include <typeinfo>

#include <format>
#include <locale>

#include <memory_resource>

// import std.core; // needs /MD /EHsc /std:c++latest /experimental:module ...

import Utils.Numbers;
import helloworld;
import Utils.Generators;
import Utils.Pmr;
import Playground.MoveSemantics;

auto dice() {
  static std::uniform_int_distribution<int> distr{1, 6};
  static std::random_device device;
  // static std::mt19937 engine{device()};
  static std::default_random_engine engine{device()};
  return distr(engine);
}

#define bool_to_string(x) (x ? "true" : "false")

template <typename T> void print_power_of_two(const T &value) {
  std::cout << "is_power_of_two(" << value << ") : where the value is of type "
            << typeid(value).name() << " = "
            << bool_to_string(is_power_of_two(value)) << std::endl;
}

template <typename... Ts>
std::string stringformat(const std::string &fmt, Ts... args) {
  size_t size = std::snprintf(nullptr, 0, fmt.c_str(), args...) +
                1; // Extra space for '\0'
  std::unique_ptr<char[]> buf(new char[size]);
  std::snprintf(buf.get(), size, fmt.c_str(), args...);
  return std::string(buf.get(),
                     buf.get() + size - 1); // We don't want the '\0' inside
}
#ifdef _WIN32
#include <Windows.h>
#endif

int main(int, char **) {
  using namespace std::ranges;

#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
  setvbuf(stdout, nullptr, _IONBF, 0);
#endif

  std::locale::global(std::locale("pt_BR.UTF-8"));

  hello();

  auto fibonacci = utils::generators::fibonacci();

  for (int i = 0; true; i++) {
    try {
      std::cout << "Fibonacci(" << i << ") = " << fibonacci() << std::endl;
    } catch (const std::runtime_error &e) {
      std::cout << e.what() << std::endl;
      break;
    }
  }

  // Not working...
  // auto count { utils::generators::co_counter(10) };
  // for( const auto & val: count) {
  //     std::cout << "Counter = " << val << std::endl;
  //     if( val > 20 )
  //         break;
  // }

  using var_numbers =
      std::variant<unsigned char, char, int, unsigned int, float, double,
                   long double, long long, unsigned long long>;

  std::vector<var_numbers> nums{-16, -16.0, 0,   1,     1.0,   8,      8.0,
                                39,  39.0,  128, 128.5, 128.0, 1u,     1.0f,
                                8u,  8.0f,  39u, 39.0f, 128u,  128.5f, 128.0f};

  auto ints{nums | views::filter([](const auto &n) {
              return std::holds_alternative<int>(n);
            }) |
            views::transform([](const auto &n) { return std::get<int>(n); })};

  auto dbls{
      nums | views::filter([](const auto &n) {
        return std::holds_alternative<double>(n);
      }) |
      views::transform([](const auto &n) { return std::get<double>(n); })};

  std::cout << std::fixed << std::setw(3) << std::setprecision(1);

  std::cout << "Integers: " << std::endl;
  for (const auto &value : ints) {
    print_power_of_two(value);
  }

  std::cout << "Doubles: " << std::endl;
  for (const auto &value : dbls) {
    print_power_of_two(value);
  }

  std::cout << "Everything: " << std::endl;
  for (const auto &value : nums) {
    // templates must be staticly evaluated, so, the next line is not valid
    // print_power_of_two(std::get<value.index()>(value));

    // this is the silly way to do it
    // switch(value.index()) {
    //     case 0:
    //         print_power_of_two(std::get<0>(value));
    //         break;
    //     case 1:
    //         print_power_of_two(std::get<1>(value));
    //         break;
    //     case 2:
    //         print_power_of_two(std::get<2>(value));
    //         break;
    //     case 3:
    //         print_power_of_two(std::get<3>(value));
    //         break;
    //     case 4:
    //         print_power_of_two(std::get<4>(value));
    //         break;
    //     case 5:
    //         print_power_of_two(std::get<5>(value));
    //         break;
    //     case 6:
    //         print_power_of_two(std::get<6>(value));
    //         break;
    //     case 7:
    //         print_power_of_two(std::get<7>(value));
    //         break;
    //     case 8:
    //         print_power_of_two(std::get<7>(value));
    //         break;
    //     default:
    //         std::cout << "Unknown type" << std::endl;
    // }

    // I don't know what kind of sorcery is behind of this... but it works...
    std::visit([](const auto &n) { print_power_of_two(n); }, value);
  }

  auto result{nums | views::filter([](const auto &value) {
                return std::visit(
                    [](const auto &x) -> bool { return is_power_of_two(x); },
                    value);
              })};

  std::vector<var_numbers> result_vec{result.begin(), result.end()};
  std::ranges::sort(result_vec, [](const auto &a, const auto &b) {
    return std::visit(
        [](const auto &x, const auto &y) -> bool {
          return static_cast<long double>(x) < static_cast<long double>(y);
        },
        a, b);
  });

  for (const auto &value : result_vec) {
    std::visit(
        [](const auto &x) { std::cout << "Power of two: " << x << std::endl; },
        value);
  }

  // std::for_each(std::execution::par, result.begin(), result.end(), [](const
  // auto &value) {
  //     std::visit([](const auto &x) { std::cout << "Power of two: " << x <<
  //     std::endl; }, value);
  // });

  std::cout << "🌄String format: "
            << stringformat("%s é de valor %f", "PI", 3.14) << std::endl;
  //   std::cout << std::format("String format: PI é de valor {}", 3.14)
  //             << std::endl;

  std::array<std::uint8_t, 1024> buffer{};
  std::pmr::monotonic_buffer_resource mem_resource(buffer.data(),
                                                   buffer.size());

  auto vet = create_container<std::pmr::vector<std::pmr::string>>(
      &mem_resource, "Hello", "World", "Hello Long String",
      "Another Long String");

  for (const auto &str : vet) {
    std::cout << str << std::endl;
  }

  runMoveSemanticsTests();

  return 0;
}
