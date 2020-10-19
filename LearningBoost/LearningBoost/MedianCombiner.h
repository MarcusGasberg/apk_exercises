#pragma once
#include <algorithm>
#include <iostream>
#include <vector>

template<typename T>
struct median_combiner
{
    typedef T result_type;

    template<typename InputIterator>
    T operator()(InputIterator first, InputIterator last) const
    {
	    std::vector<T> values;

        while (first != last) {
        	values.push_back(*first);
            ++first;
        }

        std::sort(values.begin(), values.end());

        int median_idx = round(values.size() / 2);
    	
        return values[median_idx];
    }
};
