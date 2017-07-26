#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include <SDL.h>
#include "SDLUtils.h"

class Game {
private:
	SDL_Renderer* windowRenderer;
	Uint32 frames;

	SDL_TexturePtr background;
	SDL_TexturePtr text;
	TTF_FontPtr font;
public:
	Game(SDL_Renderer* windowRenderer);
	virtual ~Game();
	static const int FPS = 60;
	static const int WIDTH = 800;
	static const int HEIGHT = 633;
	constexpr static const char* TITLE = "Hello, World!";

	void run();
	Uint32 getFrames() { return frames; };
	bool isFinished();
	SDL_Renderer* getWindowRenderer() { return windowRenderer; } ;
};

#endif /* SRC_GAME_H_ */
