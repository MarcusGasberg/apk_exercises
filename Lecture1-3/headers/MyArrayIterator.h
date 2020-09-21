#pragma once
#include <iterator>

template <typename T>
class MyArrayIterator : public std::iterator<std::input_iterator_tag, T>
{
private:
	T *val_;

public:
	explicit MyArrayIterator(T *arr) : val_{arr} {}
	MyArrayIterator(const MyArrayIterator &my_array_iterator) : val_{my_array_iterator.val_} {}
	MyArrayIterator &operator++()
	{
		++val_;
		return *this;
	}
	MyArrayIterator operator++(int)
	{
		MyArrayIterator tmp{*this};
		operator++();
		return tmp;
	}
	bool operator==(const MyArrayIterator &rhs) const { return val_ == rhs.val_; }
	bool operator!=(const MyArrayIterator &rhs) const { return val_ != rhs.val_; }
	T operator*() { return *val_; }
};
