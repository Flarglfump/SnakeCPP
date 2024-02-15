#include <windows.h>
#include <utility>
#include <ncurses/ncurses.h>
#include "ScreenBuffer.hpp"

namespace SnakeGame {
    SnakeGame::ScreenBuffer getScreenBuf() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int columns, rows;
    
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        return SnakeGame::ScreenBuffer(columns, rows);
    }

    void microsleep(double microseconds) {
        Sleep(microseconds);
    }
}