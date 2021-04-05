#ifndef _HELPERS_HPP_
#define _HELPERS_HPP_

#include <ctime>
#include <cstdlib>

namespace Helpers {
    template<typename T>
    T min(T x, T y)
    {
        return x < y ? x : y;
    }

    template<typename T>
    T max(T x, T y)
    {
        return x > y ? x : y;
    }

    int32_t getRandInt(int32_t min_value, int32_t max_value)
    {
        if (min_value >= max_value)
            return 0;

        srand((unsigned) time(0));
        return rand() % max_value + min_value;
    }
};

#endif