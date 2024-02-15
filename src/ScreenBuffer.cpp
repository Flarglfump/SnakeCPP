#include "ScreenBuffer.hpp"

SnakeGame::ScreenBuffer::ScreenBuffer() {
    width = 20;
    height = 20;
    data = std::vector<std::string> (width, std::string(height, ' '));
}

SnakeGame::ScreenBuffer::ScreenBuffer(int w, int h) {
    width = w;
    height = h;
    data = std::vector<std::string> (h, std::string(w, ' '));
}

void SnakeGame::ScreenBuffer::clear() {
    for (std::string &row : data) {
        std::fill(row.begin(), row.end(), ' ');
    }
}
void SnakeGame::ScreenBuffer::draw(int x, int y, char ch) {
    if (x < 0 || x >= width) {
        throw std::out_of_range("Error: x coordinate (" + std::to_string(x) + ") out of range");
    } else if (y < 0 || y >= height) {
        throw std::out_of_range("Error: y coordinate (" + std::to_string(y) + ") out of range");
    }
    else {
        data[y][x] = ch;
    }
}

void SnakeGame::ScreenBuffer::drawBorder() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if ((x == 0 || x == width - 1) && (y == 0 || y == height - 1)) { // Corners
                draw(x, y, '+');
            } else if (x == 0 || x == width - 1) {
                draw(x, y, '|');
            } else if (y == 0 || y == height - 1) {
                draw(x, y, '-');
            }
        }
    }
}

void SnakeGame::ScreenBuffer::print() const {
    for (std::string row : data) {
        std::cout << row << '\n';
    }
}

int SnakeGame::ScreenBuffer::getWidth() const {
    return width;
}
int SnakeGame::ScreenBuffer::getHeight() const {
    return height;
}