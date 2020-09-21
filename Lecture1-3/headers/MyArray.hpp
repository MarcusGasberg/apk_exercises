#pragma once

#include <cstddef>
#include "./MyArrayIterator.h"

template <typename T>
class MyArray
{
private:
	int size_;
	T *container_;

public:
	explicit MyArray(int n);
	MyArray(MyArray<T> const &rhs);
	~MyArray();
	void fill(const T &object);
	MyArrayIterator<T> begin() const;
	MyArrayIterator<T> end() const;
	T &operator[](int i) const;
	size_t get_size() const;
	MyArray<T> &operator=(MyArray<T> const &rhs);
	typedef T value_type;
};

template <typename T>
class MyArray<T *>
{
private:
	int size_;
	T **container_;

public:
	explicit MyArray(int n);
	MyArray(MyArray<T *> const &rhs);
	~MyArray();
	void fill(const T &object);
	MyArrayIterator<T *> begin() const;
	MyArrayIterator<T *> end() const;
	T *&operator[](int i) const;
	size_t get_size() const;
	MyArray<T *> &operator=(MyArray<T *> const &rhs);
	typedef T value_type;
};

template <typename T>
MyArray<T>::MyArray(int n) : size_{n}
{
	container_ = new T[size_];
}

template <typename T>
MyArray<T *>::MyArray(int n) : size_{n}
{
	container_ = new T *[size_];
}

template <typename T>
MyArray<T>::MyArray(MyArray<T> const &rhs)
{
	size_ = rhs.get_size();
	container_ = new T[size_];

	for (size_t i = 0; i < size_; i++)
	{
		container_[i] = T{rhs[i]};
	}
}

template <typename T>
MyArray<T *>::MyArray(MyArray<T *> const &rhs)
{
	size_ = rhs.get_size();
	container_ = new T *[size_];

	for (size_t i = 0; i < size_; i++)
	{
		container_[i] = new T(*rhs.container_[i]);
	}
}

template <typename T>
MyArray<T> &MyArray<T>::operator=(MyArray<T> const &rhs)
{
	auto tmp{rhs};

	delete[] container_;

	size_ = tmp.get_size();
	container_ = new T[size_];

	for (size_t i = 0; i < size_; i++)
	{
		container_[i] = T(tmp[i]);
	}

	return *this;
}

template <typename T>
MyArray<T *> &MyArray<T *>::operator=(MyArray<T *> const &rhs)
{
	auto tmp{rhs};

	for (size_t i = 0; i < this->size_; i++)
	{
		delete container_[i];
	}

	size_ = tmp.get_size();
	container_ = new T *[size_];

	for (size_t i = 0; i < size_; i++)
	{
		container_[i] = new T(*tmp[i]);
	}

	return *this;
}

template <typename T>
MyArray<T>::~MyArray() { delete[] container_; }

template <typename T>
MyArray<T *>::~MyArray()
{
	for (size_t i = 0; i < this->size_; i++)
	{
		delete container_[i];
	}
}

template <typename T>
void MyArray<T>::fill(const T &object)
{
	for (size_t i = 0; i < size_; i++)
	{
		container_[i] = T{object};
	}
}

template <typename T>
void MyArray<T *>::fill(const T &object)
{
	for (size_t i = 0; i < size_; i++)
	{
		container_[i] = new T(object);
	}
}

template <typename T>
MyArrayIterator<T> MyArray<T>::begin() const { return MyArrayIterator<T>(&container_[0]); }

template <typename T>
MyArrayIterator<T *> MyArray<T *>::begin() const { return MyArrayIterator<T *>(&container_[0]); }

template <typename T>
MyArrayIterator<T> MyArray<T>::end() const
{
	return size_ > 0 ? MyArrayIterator<T>(&container_[size_ - 1] + 1) : MyArrayIterator<T>(&container_[0]);
}
template <typename T>
MyArrayIterator<T *> MyArray<T *>::end() const
{
	return size_ > 0 ? MyArrayIterator<T *>(&container_[size_ - 1] + 1) : MyArrayIterator<T*>(&container_[0]);
}

template <typename T>
size_t MyArray<T>::get_size() const { return size_; }

template <typename T>
size_t MyArray<T *>::get_size() const { return size_; }

template <typename T>
T &MyArray<T>::operator[](int i) const
{
	return container_[i];
}

template <typename T>
T *&MyArray<T *>::operator[](int i) const
{
	return container_[i];
}

template <typename T>
MyArrayIterator<T> my_find(MyArrayIterator<T> first, MyArrayIterator<T> last, const T &v)
{
	auto current = first;
	while (current != last)
	{
		if (*current == v)
		{
			break;
		}
		++current;
	}
	return current;
}

template <typename T, typename V>
MyArrayIterator<T *> my_find(MyArrayIterator<T *> first, MyArrayIterator<T *> last, const V &v)
{
	auto current = first;
	while (current != last)
	{
		if (**current == v)
		{
			break;
		}
		++current;
	}
	return current;
}

template <typename Container>
typename Container::value_type my_accumulate(const Container &container)
{
	typename Container::value_type m = typename Container::value_type();

	for (auto val : container)
	{
		m += val;
	}

	return m;
}