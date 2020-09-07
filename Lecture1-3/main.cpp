#include "./headers/SharedPtr.hpp"
#include <iostream>
#include <string>

struct log_functor
{
  void test() { std::cout << "TEST" << std::endl; }
};

int main(int, char **)
{
  std::string *s  = new std::string("asd");
  std::string *s2 = new std::string("qwe");
  auto         i  = new int(102);

  SharedPtr<std::string> p{s};

  SharedPtr<std::string> p2{p};

  SharedPtr<std::string> p3{s2};
  p3 = p2;

  std::cout << "p: " << *p << std::endl;
  std::cout << "p2: " << *p2 << std::endl;
  if (p3) std::cout << "p3: " << *p3 << std::endl;

  if (p3 == p2) std::cout << "p3 == p2" << std::endl;

  auto testLambda = [](auto s) {
    std::cout << "TEST: " << *s << std::endl;
    delete s;
  };

  auto p4 = new SharedPtr<int>(i, testLambda);

  delete p4;

  return 0;
}
