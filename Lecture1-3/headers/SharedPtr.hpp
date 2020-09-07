#ifndef __SHAREDPTR_H__
#define __SHAREDPTR_H__

#include "Teardown.hpp"
#include <cassert>
#include <iostream>
#include <stddef.h>

template <typename T> class SharedPtr
{
private:
  T *           raw_ptr;
  mutable int * n_shared;
  void          clean_up_ptr();
  ITeardown<T> *teardown;

public:
  template <typename D>
  SharedPtr(T *t, D d)
      : raw_ptr{t}, n_shared{new int(1)}, teardown{new TeardownFunctor<T, D>(d)}
  {
  }

  SharedPtr(T *t) : raw_ptr{t}, n_shared{new int(1)}, teardown{nullptr} {};
  explicit SharedPtr(const SharedPtr<T> &toCopy);
  ~SharedPtr();

  SharedPtr<T> &operator=(const SharedPtr<T> &rhs);
  T &           operator*();
  T *           operator->();
  bool          operator==(const SharedPtr<T> &rhs);
  explicit      operator bool() const;

  size_t count();
};

template <typename T> void SharedPtr<T>::clean_up_ptr()
{
  (*this->n_shared)--;
  std::cout << "Count: " << (*this->n_shared) << std::endl;
  if (count() < 1 && this->raw_ptr != nullptr)
  {
    if (this->teardown != nullptr)
    {
      (*this->teardown)(this->raw_ptr);
    }
    else
    {
      delete this->raw_ptr;
    }
  }
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T> &toCopy) : SharedPtr(toCopy.raw_ptr)
{
  (*toCopy.n_shared)++;
  this->n_shared = toCopy.n_shared;
  this->teardown = toCopy.teardown;
  std::cout << "Copy Constructor: " << (*this->n_shared) << std::endl;
}

template <typename T> SharedPtr<T>::~SharedPtr() { clean_up_ptr(); }

template <typename T>
SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<T> &rhs)
{

  assert(&rhs != this);

  clean_up_ptr();

  (*rhs.n_shared)++;

  this->n_shared = rhs.n_shared;
  this->raw_ptr  = rhs.raw_ptr;

  if (this->teardown ! = nullptr)
  {
    delete this->teardown;
  }
  this->teardown = rhs.teardown;

  std::cout << "Assignment: " << (*this->n_shared) << std::endl;

  return *this;
}

template <typename T> T &SharedPtr<T>::operator*() { return *this->raw_ptr; }

template <typename T> T *SharedPtr<T>::operator->() { return this->raw_ptr; }

template <typename T> bool SharedPtr<T>::operator==(const SharedPtr<T> &rhs)
{
  return this->raw_ptr == rhs.raw_ptr;
}

template <typename T> SharedPtr<T>::operator bool() const
{
  return this->raw_ptr != nullptr;
}

template <typename T> size_t SharedPtr<T>::count() { return *this->n_shared; }

#endif // __SHAREDPTR_H__