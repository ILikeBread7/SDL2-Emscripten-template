#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include <SDL.h>
#include "SDLUtils.h"
#include "AudioSystem.h"

class Game {
private:
	SDL_Renderer* windowRenderer;
	AudioSystem* audioSystem;
	Uint32 frames;

	SDL_TexturePtr background;
	SDL_TexturePtr text;
	TTF_FontPtr font;

	AudioMusic music;
	AudioChunk chunk;

	bool keepRunning;

	#ifndef __EMSCRIPTEN__
		void quitCalled();
	#endif
public:
	Game(SDL_Renderer* windowRenderer, AudioSystem* audioSystem);
	virtual ~Game();
	static const int FPS = 60;
	static const int WIDTH = 800;
	static const int HEIGHT = 633;
	constexpr static const char* TITLE = "Hello, World!";

	void run();
	Uint32 getFrames() { return frames; };
	bool isFinished();
	void handleEvents();
};

#endif /* SRC_GAME_H_ */
