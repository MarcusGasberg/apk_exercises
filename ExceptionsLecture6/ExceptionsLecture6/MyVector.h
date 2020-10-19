#pragma once

template <typename T>
class MyVector
{
public:
    explicit MyVector(int capacity = 10);

    MyVector(const MyVector& other);

    MyVector& operator=(const MyVector& other);

    ~MyVector();

    int size() const;

    T& back();

    void push_back(const T& t);
    void pop_back();

    void insert(const T& t, size_t n);

    T* begin();
    T* end();

    T& operator [](size_t i);
private:
    size_t capacity_;
    size_t size_;
    T* data_; /* Contains the actual elements - data on the heap */
};


#include <algorithm>

template <typename T>
MyVector<T>::MyVector(const int capacity): capacity_(capacity), size_(0), data_(new T[capacity])
{
}

template <typename T>
MyVector<T>::MyVector(const MyVector& other) : capacity_(other.capacity_), size_(other.size_), data_(new T[other.size()])
{
    std::copy(other.data_, other.data_ + other.size(), data_);
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other)
{
}

template <typename T>
MyVector<T>::~MyVector()
{
    delete[] data_;
}

template <typename T>
int MyVector<T>::size() const
{
    return size_;
}

template <typename T>
T& MyVector<T>::back()
{
    return *(data_ + size_);
}

template <typename T>
void MyVector<T>::push_back(const T& t)
{
    if (capacity_ == size_)
    {
        T* tmp = new T[capacity_ * 2];

        std::copy(data_, data_ + size(), tmp);
        std::swap(data_, tmp);
        delete[] tmp;

        capacity_ *= 2;
    }

    data_[size_] = t;
    ++size_;
}

template <typename T>
void MyVector<T>::pop_back()
{
    size_ = size_ > 0 ? size_ - 1 : 0;
}

template <typename T>
void MyVector<T>::insert(const T& t, size_t n)
{
    if(n > size_)
    {
        throw std::exception("Index out of bounds");
    }

    if (capacity_ == size_)
    {
        T* tmp = new T[capacity_ * 2];

        std::copy(data_, data_ + size(), tmp);
        std::swap(data_, tmp);
        delete[] tmp;

        capacity_ *= 2;
    }

    T* result = new T[size_ + 1];

    std::copy(data_, data_ + n, result);
    std::copy(data_ + n, data_ + size_, result + n + 1);
    result[n] = t;


    std::copy(result, result + size_ + 1, data_);
    ++size_;
}

template <typename T>
T* MyVector<T>::begin()
{
    return data_;
}

template <typename T>
T* MyVector<T>::end()
{
    return data_ + size_;
}

template <typename T>
T& MyVector<T>::operator[](size_t i)
{
    return data_[i];
}