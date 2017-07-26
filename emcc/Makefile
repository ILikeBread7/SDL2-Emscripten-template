CC = em++
SRC_DIR = ..\src
SOURCES = $(shell where /r $(SRC_DIR) *.cpp)
ASSETS = ../assets
PROJECT_NAME = sdl_template
all:
	$(CC) $(SOURCES) -O3 -std=c++1y -s TOTAL_MEMORY=67108864 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS="[""png""]" -s USE_SDL_TTF=2 --js-library audio-library.js --preload-file $(ASSETS) -o $(PROJECT_NAME).js

.PHONY: clean
clean:
	del $(PROJECT_NAME).data, $(PROJECT_NAME).js, $(PROJECT_NAME).js.mem