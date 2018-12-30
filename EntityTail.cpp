#include "EntityTail.h"
EntityTail::EntityTail(int distanceFromHead, int size, int direction) {
    xPos = 0;
    yPos = 0;
    facing = direction;
    width = size;
    height = size;
    dFH = distanceFromHead;
}

void EntityTail::update(float timeStep) {
    GameObject::update(timeStep);
    if (tail != nullptr) {
        tail->update(timeStep);
    }
}

void EntityTail::render(SDL_Renderer *r) {
    GameObject::render(r);
    if (tail != nullptr) {
        tail->render(r);
    }
}

void EntityTail::moveToPosition(int x, int y) {
    if (tail != nullptr) {
        tail->moveToPosition(xPos,yPos);
    }
    setPos(x, y);
    setBounds((int)xPos,(int)yPos, width, height, 0,0);
}

void EntityTail::addTail(EntityTail* newTail) {
    if (tail == nullptr) {
        tail = newTail;
    } else {
        tail->addTail(newTail);
    }
}

void EntityTail::flag(bool flag) {
    if (tail != nullptr) {
        tail->flag(flag);
    }
    flagged = flag;
}

EntityTail::~EntityTail() {
	tail = nullptr;
}
