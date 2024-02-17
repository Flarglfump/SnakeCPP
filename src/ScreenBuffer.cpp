#include "ScreenBuffer.hpp"

SnakeGame::ScreenBuffer::ScreenBuffer() {
    initscr();

    // Set up colors
    if (has_colors()) {
        start_color();
        init_pair(APPLE_COLOR_PAIR, COLOR_RED, COLOR_BLACK);
        init_pair(SNAKE_COLOR_PAIR, COLOR_GREEN, COLOR_BLACK);
    }

    win = stdscr;
    getmaxyx(win, height, width);

    // Draw border on screen
    drawBorder();
    // Set cursor at top left of screen
    wmove(win, 0, 0);
    apples.clear();
}

SnakeGame::ScreenBuffer::ScreenBuffer(WINDOW * win) {
    initscr();

    // Set up colors
    if (has_colors()) {
        start_color();
        init_pair(APPLE_COLOR_PAIR, COLOR_RED, COLOR_BLACK);
        init_pair(SNAKE_COLOR_PAIR, COLOR_GREEN, COLOR_BLACK);
    }

    this->win = win;
    getmaxyx(win, height, width);

    // Draw border on screen
    drawBorder();
    // Set cursor at top left of screen
    wmove(win, 0, 0);
    apples.clear();
}

void SnakeGame::ScreenBuffer::clear() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; 0 < width; x++) {
            mvwaddch(win, y, x, ' ');
        }
    } 
}

void SnakeGame::ScreenBuffer::clearInner() {
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            mvwaddch(win, y, x, ' ');
        }
    } 
}

void SnakeGame::ScreenBuffer::draw(int x, int y, char ch, int colorPair) {
    if (x < 0 || x >= width) {
        throw std::out_of_range("Error: x coordinate (" + std::to_string(x) + ") out of range");
    } else if (y < 0 || y >= height) {
        throw std::out_of_range("Error: y coordinate (" + std::to_string(y) + ") out of range");
    }
    else {
        mvwaddch(win, y, x, ch);
    }
}

void SnakeGame::ScreenBuffer::spawnApple(int x, int y) {
    // Do nothing if apple already exists in position
    for (auto& apple : apples) {
        if (apple.first == x && apple.second == y) {
            return; 
        }
    }

    if (x < 0 || x >= width) {
        throw std::out_of_range("Error: x coordinate (" + std::to_string(x) + ") out of range");
    } else if (y < 0 || y >= height) {
        throw std::out_of_range("Error: y coordinate (" + std::to_string(y) + ") out of range");
    }
    else {
        // Add to list of apples
        apples.push_back(std::make_pair(x, y));
    }
}
void SnakeGame::ScreenBuffer::removeApple(int x, int y) {
    int i = 0;
    for (auto& apple : apples) {
        if (apple.first == x && apple.second == y) {
            apples.erase(apples.begin() + i);
            return;
        }
        i++;
    }
}


void SnakeGame::ScreenBuffer::drawApples() {
    for (auto & apple : apples) {
        wattr_on(win, COLOR_PAIR(APPLE_COLOR_PAIR), NULL);
        mvwaddch(win, apple.second, apple.first, ACS_DIAMOND);
        wattr_off(win, COLOR_PAIR(APPLE_COLOR_PAIR), NULL);
    }
}

void SnakeGame::ScreenBuffer::drawBorder() {
    wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
}

bool SnakeGame::ScreenBuffer::isApple(int x, int y) const {
    for (auto & apple : apples) {
        if (apple.first == x && apple.second == y) {
            return true;
        }
    }
    return false;
}
bool SnakeGame::ScreenBuffer::isWall(int x, int y) const {
    return (x <= 0 || x >= width - 1 || y <= 0 || y >= height - 1);
}
void SnakeGame::ScreenBuffer::print() const {
    wrefresh(win);
}

int SnakeGame::ScreenBuffer::getWidth() const {
    return width;
}
int SnakeGame::ScreenBuffer::getHeight() const {
    return height;
}

WINDOW * SnakeGame::ScreenBuffer::getWindow() {
    return win;
}