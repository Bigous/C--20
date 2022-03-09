module;

#include <iostream>

export module helloworld;

export void hello() {
    std::cout << "Hello, module!" << std::endl;
}