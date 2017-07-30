#ifndef SRC_SDLUTILS_H_
#define SRC_SDLUTILS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#ifndef __EMSCRIPTEN__
	#include <SDL_mixer.h>
#endif

#include <memory>
#include <functional>

typedef std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture*)>> SDL_TexturePtr;
typedef std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface*)>> SDL_SurfacePtr;
typedef std::unique_ptr<TTF_Font, std::function<void(TTF_Font*)>> TTF_FontPtr;
typedef std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> SDL_WindowPtr;
typedef std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>> SDL_RendererPtr;

namespace SDLUtils {

	inline SDL_TexturePtr uptr(SDL_Texture* ptr) { return SDL_TexturePtr(ptr, SDL_DestroyTexture); };
	inline SDL_SurfacePtr uptr(SDL_Surface* ptr) { return SDL_SurfacePtr(ptr, SDL_FreeSurface); };
	inline TTF_FontPtr uptr(TTF_Font* ptr) { return TTF_FontPtr(ptr, TTF_CloseFont); };
	inline SDL_WindowPtr uptr(SDL_Window* ptr) { return SDL_WindowPtr(ptr, SDL_DestroyWindow); };
	inline SDL_RendererPtr uptr(SDL_Renderer* ptr) { return SDL_RendererPtr(ptr, SDL_DestroyRenderer); };

	inline SDL_TexturePtr loadTexture(const char* filepath, SDL_Renderer* renderer) { return uptr(IMG_LoadTexture(renderer, filepath)); };
	inline TTF_FontPtr loadFont(const char* filepath, int size) { return uptr(TTF_OpenFont(filepath, size)); };

	void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int w, int h);
	void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y);
	SDL_TexturePtr renderText(const char* text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
	SDL_TexturePtr renderText(const char* text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer, int maxWidth);

}

#endif /* SRC_SDLUTILS_H_ */
