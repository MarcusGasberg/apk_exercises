#include "./headers/MyArray.hpp"
#include "./headers/SharedPtr.hpp"
#include "./headers/MyArrayIterator.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

void test_shared_ptr();
void test_my_array();
void test_my_ptr_array();

int main(int, char **)
{
  // test_shared_ptr();
  // test_my_array();
  //test_my_ptr_array();
  MyArray<int> n{2};
  n.fill(3);
  MyArrayIterator<int> it = n.begin();
  MyArrayIterator<int> it2 = n.end();
  std::ostream_iterator<int> out_it(std::cout, "\r\n");
  std::copy(it, it2, out_it);

  return 0;
}

void test_my_ptr_array()
{
  MyArray<std::string *> myPtr(5);
  MyArray<std::string *> myPtr2(7);
  myPtr.fill(std::string("3"));
  myPtr2.fill(std::string("123"));

  myPtr[4] = new std::string("asd");

  for (auto &&i : myPtr)
  {
    std::cout << *i << std::endl;
  }

  myPtr = myPtr2;
  MyArray<std::string *> *myPtr3 = new MyArray<std::string *>(myPtr2);

  for (auto &&i : *myPtr3)
  {
    std::cout << *i << std::endl;
  }

  delete myPtr3;

  myPtr[5] = new std::string("Hello");
  auto searchFor = std::string("Hello");
  std::stringstream out;
  out << "Looking for '" << searchFor << "': ";
  auto result = my_find(myPtr.begin(), myPtr.end(), searchFor) != myPtr.end()
                    ? "Found it"
                    : "Not found";

  std::cout << out.str() << result << std::endl;
  {
    MyArray<int> myInt{5};
    MyArray<std::string> myString{20};
    myInt.fill(5);
    myString.fill("a");

    std::cout << my_accumulate(myInt) << std::endl;
    std::cout << my_accumulate(myString) << std::endl;
  }
}

void test_my_array()
{
  MyArray<int> myInt{5};
  MyArray<int> myInt2{10};
  const int i = 10;
  const int d = 3;
  myInt.fill(i);

  myInt = myInt2;
  // Test something in array
  myInt[4] = d;
  auto found = my_find(myInt.begin(), myInt.end(), d);
  if (found != myInt.end())
  {
    std::cout << "Found: " << *found << std::endl;
  }
  else
  {
    std::cout << "Didn't find: " << d << std::endl;
  }

  auto myInt3(myInt);

  // Test something not in array
  const int d2 = 69;
  found = my_find(myInt3.begin(), myInt3.end(), d2);
  if (found != myInt3.end())
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
  std::string *s = new std::string("asd");
  std::string *s2 = new std::string("qwe");
  auto i = new int(102);

  SharedPtr<std::string> p{s};

  SharedPtr<std::string> p2{p};

  SharedPtr<std::string> p3{s2};
  p3 = p2;

  std::cout << "p: " << *p << std::endl;
  std::cout << "p2: " << *p2 << std::endl;
  if (p3)
    std::cout << "p3: " << *p3 << std::endl;

  if (p3 == p2)
    std::cout << "p3 == p2" << std::endl;

  auto testLambda = [](auto s) {
    std::cout << "TEST: " << *s << std::endl;
    delete s;
  };

  auto p4 = new SharedPtr<int>(i, testLambda);

  delete p4;
}