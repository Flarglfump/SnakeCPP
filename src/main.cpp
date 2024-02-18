#include "Snake.hpp"

/* Don't Touch */
const double MICROSECONDS_PER_SECOND = 1000000.0;
double DELTA_TIME;
std::chrono::steady_clock::time_point lastUpdate;
bool KILL_GAME;
int INPUT_CHAR;

/* You can mess with this if you want */
const double MOVES_PER_SECOND = 1;
const double TIME_SCALE_MIN = 0.0;
const double TIME_SCALE_MAX = 6.0;
double TIME_SCALE = 1.0;

void initGame(SnakeGame::ScreenBuffer & screen, SnakeGame::Snake & snake);
void handleInput(SnakeGame::Snake & snake);
void updateGame(SnakeGame::ScreenBuffer & screen, SnakeGame::Snake & snake);
void display(SnakeGame::ScreenBuffer & screen);
void cleanup();
void microsleep(double microseconds);
void spawnApple(SnakeGame::ScreenBuffer & screen, SnakeGame::Snake & snake);

int main()
{
    SnakeGame::ScreenBuffer screen;
    SnakeGame::Snake snake;
    initGame(screen, snake);

    while (!KILL_GAME) {
        auto now = std::chrono::steady_clock::now();
        DELTA_TIME = std::chrono::duration_cast<std::chrono::microseconds>(now - lastUpdate).count() / MICROSECONDS_PER_SECOND;
        lastUpdate = now;

        handleInput(snake);
        updateGame(screen, snake);
        display(screen);

        microsleep(((MICROSECONDS_PER_SECOND / MOVES_PER_SECOND) / TIME_SCALE) - DELTA_TIME);
    }
    cleanup();

    printf("Goodbye!\n");

    return 0;
}

void initGame(SnakeGame::ScreenBuffer & screen, SnakeGame::Snake & snake) {
    // Initialize random seed for apple spawns
    std::srand(std::time(NULL));

    // Initialize screen for drawing game stuff
    screen = SnakeGame::ScreenBuffer();

    // Initialize snake
    std::pair<int, int> initCoords = std::make_pair(screen.getWidth() / 2, screen.getHeight() / 2);
    snake = SnakeGame::Snake(initCoords);

    // Initialize last update time and game state
    lastUpdate = std::chrono::steady_clock::now();
    KILL_GAME = false;

    // Spawn first apple
    spawnApple(screen, snake);

    // Configure for unbuffered input reading
    cbreak();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    set_escdelay(0);
    curs_set(0);
}

void handleInput(SnakeGame::Snake & snake) {
    INPUT_CHAR = getch();
    flushinp();

    // Handle Input Character
    switch(INPUT_CHAR) {
        case KEY_UP:
        case 'W':
        case 'w':
            snake.changeDirection(SnakeGame::SnakeDirection::UP);
        break;

        case KEY_DOWN:
        case 'S':
        case 's':
            snake.changeDirection(SnakeGame::SnakeDirection::DOWN);
        break;

        case KEY_LEFT:
        case 'A':
        case 'a':
            snake.changeDirection(SnakeGame::SnakeDirection::LEFT);
        break;

        case KEY_RIGHT:
        case 'D':
        case 'd':
            snake.changeDirection(SnakeGame::SnakeDirection::RIGHT);
        break;

        case 'Q':
        case 'q':
        case 27: // Esc key
            KILL_GAME = true;
    }
}

void updateGame(SnakeGame::ScreenBuffer & screen, SnakeGame::Snake & snake) {
    // Move snake
    SnakeGame::CollisionType collision = snake.move(screen);
    
    // Handle collision
    switch(collision) {
        case SnakeGame::CollisionType::APPLE:
            // Grow Snake size. Delete Apple. Spawn new apple. Increase score?
            snake.grow();
            screen.removeApple(snake.getPosition().first, snake.getPosition().second);
            spawnApple(screen, snake);
        break;

        case SnakeGame::CollisionType::WALL:
            // Game over!
            KILL_GAME = true;
        break;

        case SnakeGame::CollisionType::NONE:
        default:
            // Probably do nothing here
        break;
    }

    // Draw stuff to screen
    screen.clearInner();
    screen.drawApples();
    snake.drawSnake(screen);

    // Clamp timescale value
    SnakeGame::clamp<double>(TIME_SCALE, TIME_SCALE_MIN, TIME_SCALE_MAX);
}

void cleanup() {
    endwin();
    curs_set(1);
}

void display(SnakeGame::ScreenBuffer & screen) {
    // Display things that were drawn to screen
    screen.print();
}

void microsleep(double microseconds) {
    #ifdef _WIN32 // Windows type system
    Sleep(microseconds / 1000);
    #else // Unix type system
    usleep(microseconds);
    #endif
}

void spawnApple(SnakeGame::ScreenBuffer & screen, SnakeGame::Snake & snake) {
    int min_x = 1;
    int max_x = screen.getWidth() - 2;
    int min_y = 1;
    int max_y = screen.getHeight() - 2;
    
    int rand_x = 1;
    int rand_y = 1;

    do {
        rand_x = (std::rand() % max_x) + min_x;
        rand_y = (std::rand() % max_y) + min_y;
    } while (snake.isUsingSpace(rand_x, rand_y));

    screen.spawnApple(rand_x, rand_y);
}