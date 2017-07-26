#include "Game.h"
#include <sstream>

Game::Game(SDL_Renderer* windowRenderer) : windowRenderer(windowRenderer), frames(0) {
	background = SDLUtils::loadTexture("assets/IMG_3148.PNG", windowRenderer);
	font = SDLUtils::loadFont("assets/arial.ttf", 24);
	SDL_Color color = {255,255,0,255};
	text = SDLUtils::renderText("test text", font.get(), color, windowRenderer);
}

Game::~Game() {}

void Game::run() {
	SDLUtils::renderTexture(background.get(), windowRenderer, 0, 0, WIDTH, HEIGHT);
	SDLUtils::renderTexture(text.get(), windowRenderer, 80, 250);
	SDL_Color color = {255,0,255,255};
	std::stringstream ss;
	ss << "asdf frames: " << frames;
	SDL_TexturePtr framesText = SDLUtils::renderText(ss.str().c_str(), font.get(), color, windowRenderer);
	SDLUtils::renderTexture(framesText.get(), windowRenderer, 80, 275);
	++frames;
}

bool Game::isFinished() {
	return false;
}

