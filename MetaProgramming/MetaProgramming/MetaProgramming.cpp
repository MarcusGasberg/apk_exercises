// MetaProgramming.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Binary.h"
#include "TypeList.h"

typedef TypeList<int, NullType> IntTL;
typedef TypeList<char, TypeList<int, TypeList<long, TypeList<short, NullType>>>> MixTL;

int main()
{
    std::cout << "Binary<1011>::value = " << Binary<1011>::value << std::endl;
    // std::cout << "Binary<1012>::value = "<< Binary<1012>::value << std::endl; // OBS DOESNT WORK

    std::cout << "Contains <TL, int >::value=" << Contains<IntTL, int>::value << std::endl;

    /* Must be false */
    std::cout << "Contains <TL, std::string >::value=" << Contains<IntTL, std::string>::value << std::endl;

    std::cout << "IsSame <typename AtIndex <TL, 2>::type , int >::value" << IsSame<typename AtIndex<MixTL, 1>::type, int>::value << std::endl;

    /* Must be false */
    std::cout << "IsSame <typename AtIndex <TL, 2>::type , char >::value" << IsSame<typename AtIndex<MixTL, 2>::type, char>::value << std::endl;

     /* Must be false */
     std::cout << "Contains <typename Remove <TL, int >::type , int >::value" << Contains <typename Remove <MixTL, int >::type, int >::value << std::endl;
     PrintIT<Remove <MixTL, int >::type>();

    /* Must be true , semi test to verify that the typelist still contains a
    char */
    std::cout << "Contains <typename Remove <TL, char >::type , int >::value" <<Contains <Remove <MixTL, char >::type, int >::value << std::endl;
    PrintIT<Remove <MixTL, char >::type>();
}
