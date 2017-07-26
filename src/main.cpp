#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#ifdef __EMSCRIPTEN__
	#include <emscripten.h>
#else
	#include <SDL_mixer.h>
#endif

#include <memory>
#include <functional>
#include "SDLUtils.h"
#include "Game.h"
#include "AudioSystem.h"

#ifdef __EMSCRIPTEN__
	void mainLoopContent(void* arg) {
		((Game*)arg)->run();
	}
#endif

void cleanupSDL(int sdlInitPhase) {
	switch (sdlInitPhase) {
	#ifndef __EMSCRIPTEN__
		case 4: Mix_CloseAudio();
	#endif
	/* no break */
	case 3: TTF_Quit();
	/* no break */
	case 2: IMG_Quit();
	/* no break */
	case 1: SDL_Quit();
	}
}

void setupWindowAndStartGame() {
	SDL_WindowPtr window = SDLUtils::uptr(SDL_CreateWindow(Game::TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::WIDTH, Game::HEIGHT, SDL_WINDOW_SHOWN));
	if (window == nullptr) {
		printf("Could not create SDL2 window, error message: %s", SDL_GetError());
		return;
	}

	SDL_RendererPtr windowRenderer = SDLUtils::uptr(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
	if (windowRenderer == nullptr) {
		printf("Could not create SDL2 window renderer, error message: %s", SDL_GetError());
		return;
	}

	AudioSystem audioSystem;
	Game game(windowRenderer.get(), &audioSystem);
	#ifdef __EMSCRIPTEN__
		emscripten_set_main_loop_arg(mainLoopContent, &game, Game::FPS, 1);
	#else
		while (1) {
			Uint32 startTime = SDL_GetTicks();
			game.run();
			if (game.isFinished()) {
				break;
			}
			if (SDL_GetTicks() - startTime < 1000/Game::FPS) {
				SDL_Delay(1000/Game::FPS - (SDL_GetTicks() - startTime));
			}
		}
	#endif
}

int main(int argc, char** argv) {
	Uint32 sdlInitFlags = SDL_INIT_VIDEO |  SDL_INIT_EVENTS;
	#ifndef __EMSCRIPTEN__
		sdlInitFlags |= (SDL_INIT_AUDIO | SDL_INIT_JOYSTICK);
	#endif
	if (SDL_Init(sdlInitFlags) != 0) {
		printf("Could not initialize SDL2, error message: %s", SDL_GetError());
		return 0;
	}
	int sdlInitPhase = 1;

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		printf("Could not initialize image loading library, error message: %s", SDL_GetError());
		cleanupSDL(sdlInitPhase);
		return 0;
	}
	++sdlInitPhase;

	if (TTF_Init() != 0) {
		printf("Could not initialize image loading library, error message: %s", SDL_GetError());
		cleanupSDL(sdlInitPhase);
		return 0;
	}
	++sdlInitPhase;

	#ifndef __EMSCRIPTEN__
		if (Mix_OpenAudio(22050, MIX_INIT_OGG, 2, 4096) != 0) {
			printf("Could not initialize SDL2 mixer, error message: %s", SDL_GetError());
			cleanupSDL(sdlInitPhase);
			return 0;
		}
		++sdlInitPhase;
	#endif

	setupWindowAndStartGame();

	cleanupSDL(sdlInitPhase);
	return 0;
}

