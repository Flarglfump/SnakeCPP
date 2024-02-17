#pragma once

#include "ScreenBuffer.hpp"

namespace SnakeGame {
    enum SnakeDirection {RIGHT, LEFT, DOWN, UP};
    enum CollisionType {NONE, APPLE, WALL};
    class Snake{
    private:
        std::list<std::pair<int, int>> data;
        SnakeDirection direction;
        std::pair<int, int> lastPosition;
    public:
        Snake();
        Snake(int x, int y);
        Snake(std::pair<int, int> coords);

        void grow();
        void drawSnake(ScreenBuffer & screen);
        CollisionType move(ScreenBuffer & screen);
        void changeDirection(SnakeDirection newDirection);

        int getSize() const;
        std::pair<int,int> getPosition() const;
        bool isUsingSpace(int x, int y) const;
    };
}