#include "AudioSystem.h"
#include <stdio.h>

#ifdef __EMSCRIPTEN__
namespace AudioSystemJSLibrary {
	extern "C" {
		extern int loadMusic(const char* filepath);
		extern int loadChunk(const char* filepath);
		extern void playMusic(int music);
		extern void stopMusic();
		extern void playChunk(int chunk);
		extern void setMusicVolume(float volume);
		extern void setChunkVolume(float volume);
		extern void freeMusic(int music);
		extern void freeChunk(int chunk);
	}
}
#endif

AudioSystem::AudioSystem() {}
AudioSystem::~AudioSystem() {}
MusicUptr::~MusicUptr() {
#ifdef __EMSCRIPTEN__
	if (music != -1) {
		AudioSystemJSLibrary::freeMusic(music);
	}
#endif
}
ChunkUptr::~ChunkUptr() {
#ifdef __EMSCRIPTEN__
	if (chunk != -1) {
		AudioSystemJSLibrary::freeChunk(chunk);
	}
#endif
}

MusicUptr AudioSystem::loadMusic(const char* filepath) {
#ifdef __EMSCRIPTEN__
	return AudioSystemJSLibrary::loadMusic(filepath);
#else
	return std::move(uptr(Mix_LoadMUS(filepath)));
#endif
}

ChunkUptr AudioSystem::loadChunk(const char* filepath) {
#ifdef __EMSCRIPTEN__
	return AudioSystemJSLibrary::loadChunk(filepath);
#else
	return std::move(uptr(Mix_LoadWAV(filepath)));
#endif
}

void AudioSystem::playMusic(MusicRawPtr music) {
#ifdef __EMSCRIPTEN__
	AudioSystemJSLibrary::playMusic(music.music);
#else
	Mix_PlayMusic(music.music, -1);
#endif
}

void AudioSystem::stopMusic() {
#ifdef __EMSCRIPTEN__
	AudioSystemJSLibrary::stopMusic();
#else
	Mix_HaltMusic();
#endif
}

void AudioSystem::playChunk(ChunkRawPtr chunk) {
#ifdef __EMSCRIPTEN__
	AudioSystemJSLibrary::playChunk(chunk.chunk);
#else
	Mix_PlayChannel(-1, chunk.chunk, 0);
#endif
}

void AudioSystem::setMusicVolume(float volume) {
#ifdef __EMSCRIPTEN__
	AudioSystemJSLibrary::setMusicVolume(volume);
#else
	Mix_VolumeMusic(MIX_MAX_VOLUME * volume);
#endif
}

void AudioSystem::setChunkVolume(float volume) {
#ifdef __EMSCRIPTEN__
	AudioSystemJSLibrary::setChunkVolume(volume);
#else
	Mix_Volume(-1, MIX_MAX_VOLUME * volume);
#endif
}
