#include "Game.h"
#include <sstream>

Game::Game(SDL_Renderer* windowRenderer, AudioSystem* audioSystem, InitState initialization) : windowRenderer(windowRenderer), audioSystem(audioSystem), initialization(initialization), frames(0) {
	background = SDLUtils::loadTexture("assets/IMG_3148.PNG", windowRenderer);
	font = SDLUtils::loadFont("assets/arial.ttf", 24);
	SDL_Color color = {255,255,0,255};
	text = SDLUtils::renderText("test text", font.get(), color, windowRenderer);

	keepRunning = true;

	music = audioSystem->loadMusic("audio/bgmusic.ogg");
	chunk = audioSystem->loadChunk("audio/Cow.ogg");
}

Game::~Game() {}

void Game::run() {
	handleEvents();
	SDLUtils::renderTexture(background.get(), windowRenderer, 0, 0, WIDTH, HEIGHT);
	SDLUtils::renderTexture(text.get(), windowRenderer, 80, 250);
	SDL_Color color = {255,0,255,255};
	std::stringstream ss;
	ss << "asdf frames: " << frames;
	SDL_TexturePtr framesText = SDLUtils::renderText(ss.str().c_str(), font.get(), color, windowRenderer);
	SDLUtils::renderTexture(framesText.get(), windowRenderer, 80, 275);
	SDL_RenderPresent(windowRenderer);
	if (frames == 0) {
		audioSystem->playMusic(music.get());
		audioSystem->playChunk(chunk.get());
	}
	if (frames == 120) {
		audioSystem->stopMusic();
	}
	++frames;
}

bool Game::isFinished() {
	return !keepRunning;
}

void Game::handleEvents() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		#ifndef __EMSCRIPTEN__
			case SDL_QUIT: quitCalled(); break;
		#endif
		}
	}
}

#ifndef __EMSCRIPTEN__
	void Game::quitCalled() {
		keepRunning = false;
	}
#endif
