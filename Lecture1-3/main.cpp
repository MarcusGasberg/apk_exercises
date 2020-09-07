#include "./headers/MyArray.hpp"
#include "./headers/SharedPtr.hpp"
#include <iostream>
#include <string>

void test_shared_ptr();
void test_my_array();

int main(int, char **)
{
  // test_shared_ptr();
  test_my_array();

  return 0;
}

void test_my_array()
{
  MyArray<int>    myInt{5};
  MyArray<double> myDouble{10};
  const int       i = 10;
  const double    d = 3;
  myInt.fill(i);

  myDouble = myInt;
  // Test something in array
  myDouble[4] = d;
  auto found  = myfind(myDouble.begin(), myDouble.end(), d);
  if (found != myDouble.end())
  {
    std::cout << "Found: " << *found << std::endl;
  }
  else
  {
    std::cout << "Didn't find: " << d << std::endl;
  }

  // Test something not in array
  const double d2 = 69;
  found           = myfind(myDouble.begin(), myDouble.end(), d2);
  if (found != myDouble.end())
  {
    std::cout << "Found: " << *found << std::endl;
  }
  else
  {
    std::cout << "Didn't find: " << d2 << std::endl;
  }
}

void test_shared_ptr()
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
}