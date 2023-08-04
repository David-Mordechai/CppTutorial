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

int main()
{
    CopyingAndCopyConstructors();
    VectorOptimization();

    LOG("Hello");
}
