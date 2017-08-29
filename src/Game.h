#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include <vector>
#include <SDL.h>
#include "SDLUtils.h"
#include "AudioSystem.h"
#include "InitState.h"

class Game {
private:
	SDL_Renderer* windowRenderer;
	std::vector<SDL_JoystickPtr> controllers;
	InitState initialization;
	Uint32 frames;

	SDL_TexturePtr background;
	SDL_TexturePtr text;
	TTF_FontPtr font;

	MusicUptr music;
	ChunkUptr chunk;

	bool keepRunning;

	#ifndef __EMSCRIPTEN__
		void quitCalled();
	#endif
	void addJoystick(int index);
	void removeJoystick(int index);
	void buttonDown(Uint8 button);
	void buttonUp(Uint8 button);
	void hatEvent(Uint8 value);
	void axisEvent(Uint8 axis, Sint16 value);
	void keyDown(SDL_Keycode key);
	void keyUp(SDL_Keycode key);
	void mouseMotion(Sint32 x, Sint32 y);
	void mouseButtonDown(Uint8 button);
	void mouseButtonUp(Uint8 button);
public:
	Game(SDL_Renderer* windowRenderer, InitState initialization);
	virtual ~Game();
	static const int FPS = 60;
	static const int WIDTH = 800;
	static const int HEIGHT = 600;
	constexpr static const char* TITLE = "Hello, World!";

	void run();
	Uint32 getFrames() { return frames; };
	bool isFinished();
	void handleEvents();
};

#endif /* SRC_GAME_H_ */
