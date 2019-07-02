#include <iostream>
#include "function.hpp"

int fun(int n)
{
    return n;
}

int main()
{
    // test lambda
    {
        auto l = []() -> int { return 42; };
        mtl::Function<int()> f = l;
        std::cout << "f() = " << f() << std::endl;
    }

    // test function call
    {
        int n = 0;
        std::cin >> n;
        mtl::Function<int(int)> f2 = fun;
        std::cout << "fun(n) = " << f2(n) << std::endl;
    }

    return 0;
}