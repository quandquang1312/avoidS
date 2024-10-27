#ifndef __UTILS_
#define __UTILS_

#include <iostream>
#include <random>

namespace Utils {
    static int randomInRange(int start_range, int end_range)
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> dist(start_range, end_range);

        return dist(gen);
    }
}

#endif