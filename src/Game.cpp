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
			case SDL_JOYBUTTONDOWN: buttonDown(e.jbutton.button); break;
			case SDL_JOYBUTTONUP: buttonUp(e.jbutton.button); break;
			case SDL_JOYHATMOTION: hatEvent(e.jhat.value); break;
			case SDL_JOYAXISMOTION: axisEvent(e.jaxis.axis, e.jaxis.value); break;
			case SDL_JOYDEVICEADDED: addJoystick(e.jdevice.which); break;
			case SDL_JOYDEVICEREMOVED: removeJoystick(e.jdevice.which); break;
			case SDL_KEYDOWN: keyDown(e.key.keysym.sym); break;
			case SDL_KEYUP: keyUp(e.key.keysym.sym); break;
			case SDL_MOUSEMOTION: mouseMotion(e.motion.x, e.motion.y); break;
			case SDL_MOUSEBUTTONDOWN: mouseButtonDown(e.button.button); break;
			case SDL_MOUSEBUTTONUP: mouseButtonUp(e.button.button); break;
		}
	}
}

#ifndef __EMSCRIPTEN__
	void Game::quitCalled() {
		keepRunning = false;
	}
#endif

void Game::buttonDown(Uint8 button) {
	printf("Button down event %d\n", button);
}

void Game::buttonUp(Uint8 button) {
	printf("Button up event %d\n", button);
}

void Game::hatEvent(Uint8 value) {
	printf("Hat event %d\n", value);
}

void Game::axisEvent(Uint8 axis, Sint16 value) {
	printf("Axis event %d %d\n", axis, value);
}

void Game::addJoystick(int index) {
	controllers.push_back(SDLUtils::openJoystick(index));
}

void Game::removeJoystick(int index) {
	for (auto it = controllers.begin(); it != controllers.end(); ++it) {
		if (SDL_JoystickInstanceID(it->get()) == index) {
			controllers.erase(it);
			break;
		}
	}
}

void Game::keyDown(SDL_Keycode key) {
	printf("Key down %d\n", key);
}

void Game::keyUp(SDL_Keycode key) {
	printf("Key up %d\n", key);
}

void Game::mouseMotion(Sint32 x, Sint32 y) {
	printf("Mouse motion %d %d\n", x, y);
}

void Game::mouseButtonDown(Uint8 button) {
	printf("Mouse button down %d\n", button);
}

void Game::mouseButtonUp(Uint8 button) {
	printf("Mouse button up %d\n", button);
}
