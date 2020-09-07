#ifndef __MYARRAY_H__
#define __MYARRAY_H__

#include <stddef.h>

template <typename T> class MyArray
{
private:
  int size;
  T * container;

public:
  MyArray(int size);
  template <typename T2> MyArray(MyArray<T2> const &rhs);
  ~MyArray();
  void   fill(const T &object);
  T *    begin() const;
  T *    end() const;
  T &    operator[](int i) const;
  size_t get_size() const;

  template <typename T2> MyArray<T> &operator=(MyArray<T2> const &rhs);
};

template <typename T> MyArray<T>::MyArray(int n) : size{n}
{
  container = new T[size];
}

template <typename T>
template <typename T2>
MyArray<T>::MyArray(MyArray<T2> const &rhs)
{
  MyArray<T2> tmp(rhs);

  delete[] container;

  size      = tmp.get_size();
  container = new T[size];

  for (size_t i = 0; i < size; i++)
  {
    container[i] = T{tmp[i]};
  }
}

template <typename T>
template <typename T2>
MyArray<T> &MyArray<T>::operator=(MyArray<T2> const &rhs)
{
  delete[] container;

  size = rhs.get_size();

  for (size_t i = 0; i < size; i++)
  {
    container[i] = rhs[i];
  }

  return *this;
}

template <typename T> MyArray<T>::~MyArray() { delete[] container; }

template <typename T> void MyArray<T>::fill(const T &object)
{
  for (size_t i = 0; i < size; i++)
  {
    container[i] = T{object};
  }
}

template <typename T> T *MyArray<T>::begin() const { return &container[0]; }

template <typename T> T *MyArray<T>::end() const
{
  return size > 0 ? &container[size - 1] + 1 : &container[0];
}

template <typename T> size_t MyArray<T>::get_size() const { return size; }

template <typename T> T &MyArray<T>::operator[](int i) const
{
  return container[i];
}

template <typename T> T *myfind(T *first, T *last, const T &v)
{
  T *current = first;
  while (current != last)
  {
    if (*current == v)
    {
      break;
    }
    current++;
  }
  return current;
}

#endif // __MYARRAY_H__