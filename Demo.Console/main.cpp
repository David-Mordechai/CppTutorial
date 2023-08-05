#include <functional>
#include <iostream>

#include "CopyingAndCopyConstructors.h"
#include "VectorOptimization.h"

#ifdef _DEBUG
// macro example, compiler preprocess
#define LOG(x) std::cout << (x) << std::endl
#else
// the LOG will be removed at compilation time in release mode
#define LOG(x)
#endif

namespace func_pointers
{
    void print_value(const int value)
    {
        std::cout << "Value with PrintValue function: " << value << std::endl;
    }

    void my_for_each(const std::vector<int>& values, const std::function<void(int)>& func)
    {
        for (const int value : values)
            func(value);
    }
}

int main()
{
    CopyingAndCopyConstructors();
    VectorOptimization();
    LOG("Hello");

    const std::vector<int> values = { 1,5,4,2,3 };
    func_pointers::my_for_each(values, func_pointers::print_value);

    int b = 1;
    func_pointers::my_for_each(values, [b](const int value)
    {
	    std::cout << "Value with lambda: " << value + b << std::endl;
    });
}
