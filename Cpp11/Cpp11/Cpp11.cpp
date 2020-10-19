// Cpp11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "File.h"

int main()
{
    const char* txt = "test.txt";

    File f{ txt };

    f.write("test");

    const auto f2 = std::move(f);

    std::cout << f2.read() << std::endl;
}
