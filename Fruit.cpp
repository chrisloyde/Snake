#include "Fruit.h"

Fruit::Fruit(int worldWidth, int worldHeight, int size) {
    worldW = worldWidth;
    worldH = worldHeight;
    xPos = 0;
    yPos = 0;
    xOffset = 0;
    yOffset = 0;
    width = size;
    height = size;
    isSolid = false;

    changePos();
}

void Fruit::changePos() {
    int x = rand()%(worldW-1);
    int y = rand()%(worldH-1);

    printf("Fruit Position %d, %d\n", x, y);

    setPos(x*width, y*height);
    setBounds(xPos,yPos,width,height,0,0);
}

void Fruit::handleCollision(GameObject *other) {
    GameObject::handleCollision(other);
    changePos(); // change fruit position on collision.
}