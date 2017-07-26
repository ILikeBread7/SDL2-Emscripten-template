#include "AudioSystem.h"

#ifdef __EMSCRIPTEN__
namespace AudioSystemJSLibrary {
	extern "C" {
		extern AudioMusic loadMusic(const char* filepath);
		extern AudioChunk loadChunk(const char* filepath);
		extern void playMusic(AudioMusic music);
		extern void stopMusic();
		extern void playChunk(AudioChunk chunk);
		extern void setMusicVolume(float volume);
		extern void setChunkVolume(float volume);
	}
}
#endif

AudioSystem::AudioSystem() {}
AudioSystem::~AudioSystem() {}

AudioMusic AudioSystem::loadMusic(const char* filepath) {
#ifdef __EMSCRIPTEN__
	return AudioSystemJSLibrary::loadMusic(filepath);
#else
	musics.push_back(SDLUtils::loadMusic(filepath));
	return musics.size() - 1;
#endif
}

AudioChunk AudioSystem::loadChunk(const char* filepath) {
#ifdef __EMSCRIPTEN__
	return AudioSystemJSLibrary::loadChunk(filepath);
#else
	chunks.push_back(SDLUtils::loadChunk(filepath));
	return chunks.size() - 1;
#endif
}

void AudioSystem::playMusic(AudioMusic music) {
#ifdef __EMSCRIPTEN__
	AudioSystemJSLibrary::playMusic(music);
#else
	SDLUtils::playMusic(musics[music].get());
#endif
}

void AudioSystem::stopMusic() {
#ifdef __EMSCRIPTEN__
	AudioSystemJSLibrary::stopMusic();
#else
	Mix_HaltMusic();
#endif
}

void AudioSystem::playChunk(AudioChunk chunk) {
#ifdef __EMSCRIPTEN__
	AudioSystemJSLibrary::playChunk(chunk);
#else
	SDLUtils::playChunk(chunks[chunk].get());
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
