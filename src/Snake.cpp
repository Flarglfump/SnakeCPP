#include "Snake.hpp"

SnakeGame::Snake::Snake() {
    data.clear();
    data.push_back(std::make_pair(0, 0));
    direction = SnakeGame::SnakeDirection::RIGHT;
}
SnakeGame::Snake::Snake(int x, int y) {
    data.clear();
    data.push_back(std::make_pair(x, y));
    direction = SnakeGame::SnakeDirection::RIGHT;
}
SnakeGame::Snake::Snake(std::pair<int, int> coords) {
    data.clear();
    data.push_back(coords);
    direction = SnakeGame::SnakeDirection::RIGHT;
}
void SnakeGame::Snake::drawSnake(ScreenBuffer& screen) {
    for (std::pair<int, int>& segment : data) {
        if (segment == data.front()) {
            screen.draw(segment.first, segment.second, 'S');
        } else {
            screen.draw(segment.first, segment.second, 's');
        }
    }
}
void SnakeGame::Snake::move(bool addSegment) {
    std::pair<int, int> head = data.front();

    switch(direction) {
        case SnakeGame::SnakeDirection::UP:
            data.push_front(std::make_pair(head.first, head.second - 1));
        break;
        case SnakeGame::SnakeDirection::DOWN:
            data.push_front(std::make_pair(head.first, head.second + 1));
        break;
        case SnakeGame::SnakeDirection::LEFT:
            data.push_front(std::make_pair(head.first - 1, head.second));
        break;
        case SnakeGame::SnakeDirection::RIGHT:
        default:
            data.push_front(std::make_pair(head.first + 1, head.second));
    }
    if (!addSegment) {
        data.pop_back();
    }
}