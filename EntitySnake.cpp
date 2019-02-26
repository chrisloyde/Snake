
#include "EntitySnake.h"


EntitySnake::EntitySnake(int x, int y, int size, int worldWidth, int worldHeight) {
    worldW = worldWidth;
    worldH = worldHeight;
    facing = south;
	setPos(x, y);
	setBounds(x, y, size, size, 0, 0);
	setId(std::string("Player"));
	//updateTimer.start();
	numberOfFramesBeforeTick = 6;
}


void EntitySnake::handleCollision(GameObject *other) {
    GameObject::handleCollision(other);
    if (strcmp(other->getId(), "Fruit") == 0) {
        ++score;
        Engine *engine = Engine::getExistingInstance();
		GameObjectPool *pool = GameObjectPool::getInstance();
		if (engine != nullptr) {
            EntityTail *newTail = new EntityTail(score, width, (int) facing);
            newTail->addCamera(cam);
			newTail->init(engine->getRenderer(), gTexture, new int[1]{ 1 }, 1, 16, 16);
            newTail->setId(std::string("Tail"));
            std::cout << "New Tail Created" << std::endl;
			pool->add(*newTail, 0);
            if (tail == nullptr) {
                tail = newTail;
            } else {
                tail->addTail(newTail);
            }
        } else {
            std::cerr << "Could not load Engine in Entity Snake" << std::endl;
        }
    }
    if (strcmp(other->getId(), "Tail") == 0) {
        score = 0;
        if (tail != nullptr) {
            tail->flag(true);
            tail = nullptr;
        }
    }
}

void EntitySnake::update(float timeStep) {
    GameObject::update(timeStep);
}

void EntitySnake::slowTick() {
	GameObject::slowTick();

	int pos[2]{ (int)xPos / width, (int)yPos / height };
	getNextPosition(pos, facing, worldW, worldH);

	if (tail != nullptr) {
		tail->moveToPosition(xPos, yPos);
	}

	setPos(pos[0] * spriteW, pos[1] * spriteH);
	setBounds((int)xPos, (int)yPos, width, height, 0, 0);
	canMove = true;
}

void EntitySnake::render(SDL_Renderer *r) {
    GameObject::render(r);
}

void EntitySnake::handleEvent(SDL_Event& e) {
    GameObject::handleEvent(e);
	if (canMove) {
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
				// strictly horizontal and vertical movement
			case SDLK_w:
			case SDLK_UP:
				if (facing != south) {
					facing = north;
					canMove = false;
				}
				break;
			case SDLK_s:
			case SDLK_DOWN:
				if (facing != north) {
					facing = south;
					canMove = false;

				}
				break;
			case SDLK_a:
			case SDLK_LEFT:
				if (facing != west) {
					facing = east;
					canMove = false;

				}
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				if (facing != east) {
					facing = west;
					canMove = false;

				}
				break;
			default: break;
			}
		}
	}
}

void EntitySnake::getNextPosition(int currentPosition[], directions facing, int worldWidth, int worldHeight) {
    switch(facing) {
        case EntitySnake::north:
            currentPosition[0] = currentPosition[0];
            if (currentPosition[1] <= 0) {
                currentPosition[1] = worldHeight-1;
            } else {
                currentPosition[1] = currentPosition[1] - 1;
            }
            break;
        case EntitySnake::south:
            currentPosition[0] = currentPosition[0];
            if (currentPosition[1] >= worldHeight-1) {
                currentPosition[1] = 0;
            } else {
                currentPosition[1] = currentPosition[1]+1;
            }
            break;
        case EntitySnake::east:
            if (currentPosition[0] <= 0) {
                currentPosition[0] = worldWidth-1;
            } else {
                currentPosition[0] = currentPosition[0] - 1;
            }
            currentPosition[1] = currentPosition[1];
            break;
        case EntitySnake::west:
            if (currentPosition[0] >= worldWidth-1) {
                currentPosition[0] = 0;
            } else {
                currentPosition[0] = currentPosition[0] + 1;
            }
            currentPosition[1] = currentPosition[1];
            break;
    }
}

EntitySnake::~EntitySnake() {
	tail = nullptr;
	score = 0;
	canMove = false;
}
