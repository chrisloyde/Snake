#pragma once

#include "engine/GameObject.h"

class Fruit: public GameObject {
public:
    Fruit(int worldWidth, int worldHeight, int size);
    void changePos();
    void handleCollision(GameObject *other) override;
private:
    int worldW, worldH;
};

