#pragma once

#include "ScreenBuffer.hpp"

namespace SnakeGame {
    enum SnakeDirection {RIGHT, LEFT, DOWN, UP};
    class Snake{
    private:
        std::list<std::pair<int, int>> data;
        SnakeDirection direction;
    public:
        Snake();
        Snake(int x, int y);
        Snake(std::pair<int, int> coords);
        void drawSnake(ScreenBuffer& screen);
        void move(bool addSegment = false);
    };
}