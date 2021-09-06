#pragma once
#include "pch.h"
#include <random> 
namespace Math
{
    template <typename T>
    T random(T min, T max)
    {
        if(max < min)
        {
            max = min;
        }

    	if(min > max)
    	{
            min = max;
    	}
    	
        std::random_device rd;
        std::mt19937 e(rd());
        const std::uniform_real_distribution<T> dis(min, max);
        return dis(e);
    }

    template <>
    inline int random(int min, int max)
    {
        if (max < min)
        {
            max = min;
        }

        if (min > max)
        {
            min = max;
        }
    	
        std::random_device rd;
        std::mt19937 seed(rd());
        const std::uniform_int_distribution<> dist{ min, max };

        return dist(seed);
    }
}
