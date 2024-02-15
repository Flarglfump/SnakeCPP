#include "dependencies.hpp"

/* Don't Touch */
const double MICROSECONDS_PER_SECOND = 1000000.0;
double DELTA_TIME;
std::chrono::steady_clock::time_point lastUpdate;
bool KILL_GAME = false;

/* You can mess with this */
const double MOVES_PER_SECOND = 1;
const double TIME_SCALE_MIN = 0.0;
const double TIME_SCALE_MAX = 6.0;
double TIME_SCALE = 1.0;

void initGame(SnakeGame::ScreenBuffer & screen, SnakeGame::Snake & snake);
void processInput();
void updateGame();
void render();

int main()
{
    SnakeGame::ScreenBuffer screen;
    SnakeGame::Snake snake;
    initGame(screen, snake);

    long frame = 0;
    while (true) {
        auto now = std::chrono::steady_clock::now();
        DELTA_TIME = std::chrono::duration_cast<std::chrono::microseconds>(now - lastUpdate).count() / 1000000.0f;
        lastUpdate = now;
        std::cout << "Time Scale: " << TIME_SCALE << "\n"
                  << "deltaTime: " << DELTA_TIME << "\n" 
                  << "frame: " << frame++ << std::endl;

        processInput();
        updateGame();
        render();

        SnakeGame::microsleep(((MICROSECONDS_PER_SECOND / MOVES_PER_SECOND) / TIME_SCALE) - DELTA_TIME);
    }
    
    return 0;
}

void initGame(SnakeGame::ScreenBuffer & screen, SnakeGame::Snake & snake) {
    screen = SnakeGame::getScreenBuf();
    std::pair<int, int> initCoords = std::make_pair(screen.getWidth() / 2, screen.getHeight() / 2);
    snake = SnakeGame::Snake(initCoords);

    lastUpdate = std::chrono::steady_clock::now();
    std::cout << std::fixed << std::setprecision(7);
}

void processInput() {

}
void updateGame() {


    TIME_SCALE += 0.05;
    SnakeGame::clamp<double>(TIME_SCALE, TIME_SCALE_MIN, TIME_SCALE_MAX);
}
void render() {

}