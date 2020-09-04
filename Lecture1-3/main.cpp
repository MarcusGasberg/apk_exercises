#include "./headers/SharedPtr.hpp"
#include <iostream>
#include <string>

int main(int, char **)
{
  std::string *          s  = new std::string("asd");
  std::string *          s2 = new std::string("qwe");
  SharedPtr<std::string> p{s};

  SharedPtr<std::string> p2{p};

  SharedPtr<std::string> p3{s2};
  p3 = p2;

  std::cout << "p: " << *p << std::endl;
  std::cout << "p2: " << *p2 << std::endl;
  if (p3) std::cout << "p3: " << *p3 << std::endl;

  if (p3 == p2) std::cout << "p3 == p2" << std::endl;
  return 0;
}
