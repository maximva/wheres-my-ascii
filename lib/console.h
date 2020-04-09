#pragma once

#include <string>
#include <windows.h>
#include <iostream>
#include "playfield.h"
#include "tile.h"

// To try and display UNICODE chars
#include <io.h>
#include <fcntl.h>

namespace MyAscii {

    class Console {
        public:
            Console(void);
            Console(std::string windowTitle);

        public:
            void showPlayField(std::vector<Tile> * tiles, int fieldEdgeSize);
            // void updatePlayField(void);

            // void showScoreCard(void);
            // void updateScoreCard(void);

            // void showScoreBoard(void);
            // void updateScoreBoard(void);



        private:
            std::string windowTitle = "New window";

    };
};