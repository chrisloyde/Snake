#include "SnakeWorld.h"

SnakeWorld::SnakeWorld(int xTileNum, int yTileNum, int tileWidth, int tileHeight){

}

SnakeWorld::SnakeWorld(){

}

void SnakeWorld::getNextPosition(int currentPosition[], EntitySnake::directions facing) {
    switch(facing) {
        case EntitySnake::north:
            currentPosition[0] = currentPosition[0];
            currentPosition[1] = currentPosition[1] - 1;
            break;
        case EntitySnake::south:
            currentPosition[0] = currentPosition[0];
            currentPosition[1] = currentPosition[1] + 1;
            break;
        case EntitySnake::east:
            currentPosition[0] = currentPosition[0] - 1;
            currentPosition[1] = currentPosition[1];
            break;
        case EntitySnake::west:
            currentPosition[0] = currentPosition[0] + 1;
            currentPosition[1] = currentPosition[1];
            break;
    }
}
