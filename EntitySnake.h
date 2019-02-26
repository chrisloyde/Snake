
#pragma once

#include <vector>
#include "ruin_engine/GameObject.h"
#include "ruin_engine/Engine.h"
#include "ruin_engine/GameObjectPool.h"
#include "EntityTail.h"
//#include "SnakeRunner.h"

class EntitySnake: public GameObject {
public:
    int score = 0;
    enum directions {north = 0,south = 1,east = 2,west = 3};
    EntitySnake(int x, int y, int size, int worldWidth, int worldHeight);

    void update(float timeStep) override;
	void slowTick() override;
    void render(SDL_Renderer *r) override;
    void handleEvent(SDL_Event& e) override;
    //void init(SDL_Renderer *r, std::string path, int *numOfSpritesIn, int animNum, int sWidth, int sHeight, bool isHead);
    void handleCollision(GameObject *other) override ;
    static void getNextPosition(int currentPosition[], directions facing, int worldWidth, int worldHeight);
	~EntitySnake();
private:
    directions facing;
    EntityTail *tail = nullptr;
    float yVel = 0;
    float xVel = 0;
    int worldW, worldH;
	bool canMove = true;
	//Timer updateTimer;
};

