#ifndef __SHAREDPTR_H__
#define __SHAREDPTR_H__

#include <cassert>
#include <iostream>
#include <stddef.h>

template <typename T> class SharedPtr
{
private:
  T *          raw_ptr;
  mutable int *n_shared;
  void         clean_up_ptr();

public:
  SharedPtr(T *t);
  explicit SharedPtr(const SharedPtr<T> &toCopy);
  ~SharedPtr();
  SharedPtr &operator=(const SharedPtr<T> &rhs);
  T &        operator*();
  T *        operator->();
  bool       operator==(const SharedPtr<T> &rhs);
  explicit   operator bool() const;
  size_t     count();
};

template <typename T>
SharedPtr<T>::SharedPtr(T *t) : raw_ptr{t}, n_shared{new int(1)}
{
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T> &toCopy)
    : SharedPtr<T>(toCopy.raw_ptr)
{
  (*toCopy.n_shared)++;
  n_shared = toCopy.n_shared;
}

template <typename T> SharedPtr<T>::~SharedPtr()
{
  (*n_shared)--;
  clean_up_ptr();
}

template <typename T>
SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<T> &rhs)
{
  assert(&rhs != this);

  (*n_shared)--;
  clean_up_ptr();

  (*rhs.n_shared)++;

  n_shared = rhs.n_shared;
  raw_ptr  = rhs.raw_ptr;

  return *this;
}

template <typename T> void SharedPtr<T>::clean_up_ptr()
{
  if (count() < 1 && raw_ptr != nullptr)
  {
    delete raw_ptr;
  }
}

template <typename T> T *SharedPtr<T>::operator->() { return raw_ptr; }

template <typename T> bool SharedPtr<T>::operator==(const SharedPtr<T> &rhs)
{
  return this->raw_ptr == rhs.raw_ptr;
}

template <typename T> T &SharedPtr<T>::operator*() { return *raw_ptr; }

template <typename T> size_t SharedPtr<T>::count() { return *n_shared; }

template <typename T> SharedPtr<T>::operator bool() const { return true; }

#endif // __SHAREDPTR_H__