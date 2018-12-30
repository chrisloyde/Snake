#pragma once
#include <iostream>
#include <ctime>
#include <sstream>
#include "engine/GameRunner.h"
#include "engine/Timer.h"
#include "EntitySnake.h"
#include "Fruit.h"

#define SPRITE_SIZE 16
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class SnakeRunner : public GameRunner
{
public:
	static Texture* RED_BLOCK;
	static Texture* BLUE_BLOCK; 

	SnakeRunner();
	int run() override;
protected:
	bool init() override;
	void addEvents(SDL_Event &e) override;
	void addUpdates(float timeStep) override;
	void addRenders(SDL_Renderer *renderer) override;
	void addDeallocations() override;

private:
	EntitySnake *player;
	int screenWidth;
	int screenHeight;
	float scaleSizeX;
	float scaleSizeY;

	SDL_Rect camera;
	std::stringstream score;
	Texture scroreTexture;
};

