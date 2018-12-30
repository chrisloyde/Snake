#pragma once

#include "engine/GameObject.h"

class EntityTail: public GameObject {
public:
    EntityTail(int distanceFromHead, int size, int direction);
    void update(float timeStep) override;
    void addTail(EntityTail* newTail);
    void moveToPosition(int xPos, int yPos);
    void render(SDL_Renderer *r) override;
    void flag(bool flag);
	~EntityTail();
private:
    int dFH;
    int facing;
    EntityTail *tail = nullptr;
};

