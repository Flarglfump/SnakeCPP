#include "Snake.hpp"

SnakeGame::Snake::Snake() {
    Snake(std::make_pair(0,0));
}
SnakeGame::Snake::Snake(int x, int y) {
    Snake(std::make_pair(x,y));
}
SnakeGame::Snake::Snake(std::pair<int, int> coords) {
    data.clear();
    data.push_back(coords);
    direction = SnakeGame::SnakeDirection::RIGHT;
    lastPosition = coords;
}

void SnakeGame::Snake::grow() {
    data.push_back(lastPosition);
}

void SnakeGame::Snake::drawSnake(ScreenBuffer& screen) {
    wattr_on(screen.win, COLOR_PAIR(SNAKE_COLOR_PAIR), NULL);
    for (std::pair<int, int>& segment : data) {
        if (segment == data.front()) {
            screen.draw(segment.first, segment.second, 'S');
        } else {
            screen.draw(segment.first, segment.second, 's');
        }    
    }
    wattr_off(screen.win, COLOR_PAIR(SNAKE_COLOR_PAIR), NULL);
}

SnakeGame::CollisionType SnakeGame::Snake::move(SnakeGame::ScreenBuffer & screen) {

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
    lastPosition = data.back();
    data.pop_back();

    if (screen.isApple(data.front().first, data.front().second)) {
        return SnakeGame::CollisionType::APPLE;
    } else if (screen.isWall(data.front().first, data.front().second)) {
        return SnakeGame::CollisionType::WALL;
    }

    return SnakeGame::CollisionType::NONE;
}

void SnakeGame::Snake::changeDirection(SnakeGame::SnakeDirection newDirection) {
    switch (newDirection) {
        case SnakeGame::SnakeDirection::UP:
            if (direction != SnakeGame::SnakeDirection::DOWN) {
                direction = SnakeGame::SnakeDirection::UP;
            }
        break;
        case SnakeGame::SnakeDirection::DOWN:
            if (direction != SnakeGame::SnakeDirection::UP) {
                direction = SnakeGame::SnakeDirection::DOWN;
            }
        break;
        case SnakeGame::SnakeDirection::LEFT:
            if (direction != SnakeGame::SnakeDirection::RIGHT) {
                direction = SnakeGame::SnakeDirection::LEFT;
            }
        break;
        case SnakeGame::SnakeDirection::RIGHT:
            if (direction != SnakeGame::SnakeDirection::LEFT) {
                direction = SnakeGame::SnakeDirection::RIGHT;
            }
    }
}

int SnakeGame::Snake::getSize() const {
    return data.size();
}
std::pair<int,int> SnakeGame::Snake::getPosition() const {
    return data.front();
}

bool SnakeGame::Snake::isUsingSpace(int x, int y) const {
    for (auto& segment : data) {
        if (segment.first == x && segment.second == y) {
            return true;
        }
    }
    return false;
}