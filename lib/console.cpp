#include "Console.h"

namespace MyAscii {

    Console::Console(void)
    : Console("New window") {
    }

    Console::Console(std::string windowTitle) {
        HWND console = GetConsoleWindow();
        this->windowTitle =  windowTitle;
        SetConsoleTitleA(windowTitle.c_str());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xEC);
        ShowWindow(console, SW_MAXIMIZE);
    }

    void Console::showPlayField(std::vector<Tile> * tiles, int fieldEdgeSize) {
        COORD coordinateBufferSize;
        COORD topLeftCoordinate;
        SMALL_RECT srcWriteRect;
        HANDLE oldScreenBuffer, newScreenBuffer;
        BOOL succes;

        oldScreenBuffer = GetStdHandle(STD_OUTPUT_HANDLE);
        newScreenBuffer = CreateConsoleScreenBuffer(
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            CONSOLE_TEXTMODE_BUFFER,
            NULL);


        for (int y = 0; y < fieldEdgeSize; y++) {
            for (int x = 0; x < fieldEdgeSize; x++) {
                // 1 tile is 9 vertical and 5 horizontal characters
                const int MAP_SIZE = 45;
                CHAR_INFO map[MAP_SIZE];

                const int TILE_ARRAY_INDEX = x + (y * fieldEdgeSize);

                int TILE_CENTER = 22;

                // Display playfield on screen
                for (int j = 0; j < 45; j++) {
                    char HIDDEN_CHAR = ((*tiles)[TILE_ARRAY_INDEX].isTurned() ? (*tiles)[TILE_ARRAY_INDEX].getAsciiChar() : (*tiles)[TILE_ARRAY_INDEX].getHiddenChar());
                    int TILE_ATTRIBUTE = ((*tiles)[TILE_ARRAY_INDEX].isTurned() ? 0x31 : 0x20);

                    map[j].Char.UnicodeChar = (j == TILE_CENTER ? HIDDEN_CHAR : L' ');     // Use   L'▓' for unicode chars
                    map[j].Attributes = TILE_ATTRIBUTE;
                }

                coordinateBufferSize.Y = 5;
                coordinateBufferSize.X = 9;
                topLeftCoordinate.Y = 0;
                topLeftCoordinate.X = 0;

                // TODO CHECK MATH AND SIMPLIFY
                const int TILE_VERTICAL_WIDTH = 4;
                const int TILE_VERTICAL_BORDER = 2;

                (&srcWriteRect)->Top = ((TILE_VERTICAL_WIDTH + TILE_VERTICAL_BORDER) * y) + TILE_VERTICAL_WIDTH;               // Number of rows to the top                                          4
                (&srcWriteRect)->Left = 10 + (x * 11);             // Numbers of columns to the side                                    21
                (&srcWriteRect)->Bottom = (6 * y) + 8;
                (&srcWriteRect)->Right = 18 + (x * 11);

                succes = WriteConsoleOutputW(
                    newScreenBuffer,                    // The new ScreenBuffer
                    map,                                // The char array we want to display
                    coordinateBufferSize,               // 
                    topLeftCoordinate,
                    (&srcWriteRect)
                );
            }
        }

        SetConsoleActiveScreenBuffer(newScreenBuffer);

    }

}