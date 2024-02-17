#pragma once

#include "dependencies.hpp"

namespace SnakeGame {
    const int APPLE_COLOR_PAIR = 1;
    const int SNAKE_COLOR_PAIR = 2;
    class ScreenBuffer {
    private:
        int width, height;
        WINDOW * win;
        std::vector<std::pair<int, int>> apples;

    public:
        ScreenBuffer();
        ScreenBuffer(WINDOW * win);

        void clear();
        void clearInner();
        void draw(int x, int y, char ch, int colorPair = -1);
        void drawBorder();
        void drawApples();
        void print() const;

        void spawnApple(int x, int y);
        void removeApple(int x, int y);

        bool isApple(int x, int y) const;
        bool isWall(int x, int y) const;
        int getWidth() const;
        int getHeight() const;

        WINDOW * getWindow();

        friend class Snake;
    };
}