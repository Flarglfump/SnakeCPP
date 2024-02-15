/*
File: includes.hpp
Purpose: Handles includes and definition of headers as used by Snake Game
*/

#pragma once
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <list>
#include <thread>
#include <chrono>
#include <iomanip>

#include "Snake.hpp"

#ifdef _WIN32
#include "winstuff.hpp"
#else
#include "unixstuff.hpp"
#endif

namespace SnakeGame{
    template <class T>
    void clamp(T & val, T min, T max) {
        val = std::max(val, min);
        val = std::min(val, max);
    }
}
