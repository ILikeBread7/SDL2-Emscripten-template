#include "SDLUtils.h"

void SDLUtils::renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int w, int h) {
	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	SDL_RenderCopy(renderer, texture, nullptr, &r);
}

void SDLUtils::renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y) {
	SDL_Rect r;
	r.x = x;
	r.y = y;
	SDL_QueryTexture(texture, nullptr, nullptr, &r.w, &r.h);
	SDL_RenderCopy(renderer, texture, nullptr, &r);
}

SDL_TexturePtr SDLUtils::renderText(const char* text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) {
	SDL_SurfacePtr surface = uptr(TTF_RenderText_Blended(font, text, color));
	return uptr(SDL_CreateTextureFromSurface(renderer, surface.get()));
}

SDL_TexturePtr SDLUtils::renderText(const char* text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer, int maxWidth) {
	SDL_SurfacePtr surface = uptr(TTF_RenderText_Blended_Wrapped(font, text, color, maxWidth));
	return uptr(SDL_CreateTextureFromSurface(renderer, surface.get()));
}
