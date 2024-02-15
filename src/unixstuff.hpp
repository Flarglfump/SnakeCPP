#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <utility>
#include <ncurses.h>
#include "ScreenBuffer.hpp"

namespace SnakeGame{
    SnakeGame::ScreenBuffer getScreenBuf() {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

        return SnakeGame::ScreenBuffer(w.ws_col, w.ws_row);
    }

    void microsleep(double microseconds) {
        usleep(microseconds);
    }
}