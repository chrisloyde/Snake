#pragma once

#include "EntitySnake.h"

class SnakeWorld {
public:
    SnakeWorld(int xTileNum, int yTileNum, int tileWidth, int tileHeight);
    SnakeWorld();
    static void getNextPosition(int currentPosition[], EntitySnake::directions facing);
private:
};

