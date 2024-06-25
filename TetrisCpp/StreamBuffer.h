#pragma once

#include <iostream>
#include <algorithm>

struct membuf : public std::streambuf {
    template <size_t Size> membuf(char(&array)[Size]) {
        this->setp(array, array + Size - 1);
        std::fill_n(array, Size, 0);
    }
};

struct omemstream : virtual membuf, std::ostream {
    template <size_t Size> omemstream(char(&array)[Size]) :
        membuf(array),
        std::ostream(this)
    {
    }
};
