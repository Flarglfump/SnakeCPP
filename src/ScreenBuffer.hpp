#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <list>

namespace SnakeGame {
    class ScreenBuffer {
    private:
        int width, height;
        std::vector<std::string> data;

    public:
        ScreenBuffer();
        ScreenBuffer(int w, int h); 

        void clear();
        void draw(int x, int y, char ch);
        void drawBorder();
        void print() const;

        int getWidth() const;
        int getHeight() const;

        friend class Snake;
    };
}