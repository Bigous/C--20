module;

#include <experimental/generator>

export module Utils.Generators;

export {
namespace utils { namespace generators {

// Lambda mutation is acctually a function call from c++14.
auto fibonacci() {
    return [i=1,y=1] () mutable {
        auto ret = i;
        i = y;
        y += ret;
        return ret;
    };
}

// Lambda mutation is acctually a function call from c++14.
auto counter(int start = 0) {
    return [i=start] () mutable {
        return i++;
    };
}

std::experimental::generator<int> co_counter(const int& start = 0) {
    int counter { start };
    while(true)
        co_yield counter++;
}

}}

}