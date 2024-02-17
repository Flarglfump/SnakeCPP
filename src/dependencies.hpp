/*
File: dependencies.hpp
Purpose: Handles includes and definition of header files as used by Snake Game
*/
#pragma once

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <stdexcept>
#include <chrono>
#include <list>
#include <utility>
#include <random>

#ifdef _WIN32
#include <windows.h>
#include <ncurses/ncurses.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>
#endif

namespace SnakeGame{
    template <class T>
    void clamp(T & val, T min, T max) {
        val = std::max(val, min);
        val = std::min(val, max);
    }
}
