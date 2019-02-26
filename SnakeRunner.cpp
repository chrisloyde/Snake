#include "SnakeRunner.h"

#include "ruin_engine/TextureManager.h"

Texture* SnakeRunner::RED_BLOCK;
Texture* SnakeRunner::BLUE_BLOCK;

SnakeRunner::SnakeRunner() {
	screenWidth = 0;
	screenHeight = 0;
	scaleSizeX = 0;
	scaleSizeY = 0;
}

int SnakeRunner::run() {
	srand(time(0));
	char windowName[24] = "2DEngine: Snake";
	engine = Engine::getInstance(SCREEN_WIDTH, SCREEN_HEIGHT, windowName);
	engine->assignRenderScale(1.25F, 1.25F);

	if (engine == nullptr) {
		std::cerr << "Engine was not attached, creating one using defaults" << std::endl;
		engine = Engine::getInstance(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, nullptr);
		engine->assignRenderScale(1.0f, 1.0f);
	}

	if (pool == nullptr) {
		std::cerr << "Game Object Pool was not attached, creating one usign defaults" << std::endl;
		pool = GameObjectPool::getInstance();
	}

	init();
	GameRunner::gameLoop();
	GameRunner::kill();
	return 0;
}

bool SnakeRunner::init() {
	bool success = true;

	RED_BLOCK = TextureManager::registerTexture(engine->getRenderer(), "sprites/snake_block.png");
	BLUE_BLOCK = TextureManager::registerTexture(engine->getRenderer(), "sprites/fruit_block.png");

	int screenWidth = engine->getScreenWidth();																						// Get screen and scale values from engine.
	int screenHeight = engine->getScreenHeight();
	float scaleX = engine->getScaleX();
	float scaleY = engine->getScaleY();

	std::cout << "Loading Game Objects..." << std::endl;
	player = new EntitySnake(( screenWidth / 2) - SPRITE_SIZE, (screenHeight / 16) + SPRITE_SIZE, SPRITE_SIZE, 
		((screenWidth / 16) / scaleX), ((screenHeight / 16) / scaleY));																// Create player according to size and scale of screen.

	camera = { 0, 0, (int)(screenWidth / scaleX), (int)(screenHeight / scaleY) };													// Create camera according to size and scale of screen.
	
	/* Initialize Player */
	player->addCamera(&camera);
	player->init(engine->getRenderer(), BLUE_BLOCK, new int[1]{ 1 }, 1, SPRITE_SIZE, SPRITE_SIZE);		
	player->setId(std::string("Player"));

	pool->add(*player, 0);																												// Add Player to object pool.

	/* Initialize Fruits */
	for (int i = 0; i < 4; i++) {																									// Use a loop to create and intialize fruit objects then add them to the object pool.
		Fruit *fruit = new Fruit((screenWidth / 16) / scaleX, (screenHeight / 16) / scaleY, SPRITE_SIZE);
		fruit->init(engine->getRenderer(), RED_BLOCK, new int[1]{ 1 }, 1, SPRITE_SIZE, SPRITE_SIZE);
		fruit->addCamera(&camera);
		fruit->setId(std::string("Fruit"));
		pool->add(*fruit, 0);
	}

	if (success) {
		std::cout << "Game Objects loaded succesfuly" << std::endl;
	}
	else {
		std::cerr << "Error loading Game Objects" << std::endl;
	}

	return success;
}

void SnakeRunner::addEvents(SDL_Event &e) {

}

void SnakeRunner::addUpdates(float timeStep) {

}

void SnakeRunner::addRenders(SDL_Renderer *renderer) {
	score.str("");
	score.seekp(0);
	score << "Score: " << player->score;
	if (!scroreTexture.loadFromRenderedText(renderer, score.str().c_str(), engine->getSystemFont(), SDL_Color() = { 255,255,255,255 })) {
		std::cerr << "Unable to render Score Texture" << std::endl;
		return;
	}
	scroreTexture.render(renderer, 0, 0);
}

void SnakeRunner::addDeallocations() {
	score.flush();
	delete RED_BLOCK;
	delete BLUE_BLOCK;
}

