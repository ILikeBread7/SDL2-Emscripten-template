#ifndef SRC_AUDIOSYSTEM_H_
#define SRC_AUDIOSYSTEM_H_

#ifndef __EMSCRIPTEN__
	#include <vector>
	#include <memory>
	#include <functional>
	#include "SDLUtils.h"

	typedef std::unique_ptr<Mix_Music, std::function<void(Mix_Music*)>> Mix_MusicPtr;
	typedef std::unique_ptr<Mix_Chunk, std::function<void(Mix_Chunk*)>> Mix_ChunkPtr;

	inline Mix_MusicPtr uptr(Mix_Music* ptr) { return Mix_MusicPtr(ptr, Mix_FreeMusic); };
	inline Mix_ChunkPtr uptr(Mix_Chunk* ptr) { return Mix_ChunkPtr(ptr, Mix_FreeChunk); };
#else
	#include <utility>
#endif

class MusicRawPtr;
class MusicUptr;
class ChunkRawPtr;
class ChunkUptr;

class AudioSystem {
private:
	AudioSystem();
public:
	virtual ~AudioSystem();

	static MusicUptr loadMusic(const char* filepath);
	static ChunkUptr loadChunk(const char* filepath);
	static void playMusic(MusicRawPtr music);
	static void stopMusic();
	static void playChunk(ChunkRawPtr chunk);
	static void setMusicVolume(float volume);
	static void setChunkVolume(float volume);
};

class MusicRawPtr {
	friend class AudioSystem;
	friend class MusicUptr;

private:
#ifdef __EMSCRIPTEN__
	inline MusicRawPtr(int music) : music(music) {};
#else
	inline MusicRawPtr(Mix_Music* music) : music(music) {};
#endif
#ifdef __EMSCRIPTEN__
	int music;
#else
	Mix_Music* music;
#endif
};

class MusicUptr {
	friend class AudioSystem;

private:
#ifdef __EMSCRIPTEN__
	inline MusicUptr(int music) : music(music) {};
	int music;
#else
	inline MusicUptr(Mix_MusicPtr music) : music(std::move(music)) {};
	Mix_MusicPtr music;
#endif

public:
	MusicUptr(const MusicUptr&) = delete;
	MusicUptr& operator=(const MusicUptr&) = delete;
#ifdef __EMSCRIPTEN__
	inline MusicUptr(MusicUptr&& src) : music(src.music) { src.music = -1; };
	inline MusicUptr() : music(-1) {};
	inline MusicUptr& operator=(MusicUptr&& src) { std::swap(music, src.music); return *this; };
#else
	inline MusicUptr(MusicUptr&& src) : music(std::move(src.music)) {};
	inline MusicUptr() : music(nullptr) {};
	inline MusicUptr& operator=(MusicUptr&& u) { std::swap(music, u.music); return *this; };
#endif
	~MusicUptr();

#ifdef __EMSCRIPTEN__
	inline MusicRawPtr get() { return MusicRawPtr(music); };
#else
	inline MusicRawPtr get() { return MusicRawPtr(music.get()); };
#endif
};

class ChunkRawPtr {
	friend class AudioSystem;
	friend class ChunkUptr;

private:
#ifdef __EMSCRIPTEN__
	inline ChunkRawPtr(int chunk) : chunk(chunk) {};
#else
	inline ChunkRawPtr(Mix_Chunk* chunk) : chunk(chunk) {};
#endif
#ifdef __EMSCRIPTEN__
	int chunk;
#else
	Mix_Chunk* chunk;
#endif
};

class ChunkUptr {
	friend class AudioSystem;

private:
	ChunkUptr(const ChunkUptr&) = delete;
	ChunkUptr& operator=(const ChunkUptr&) = delete;
#ifdef __EMSCRIPTEN__
	inline ChunkUptr(int chunk) : chunk(chunk) {};
	int chunk;
#else
	inline ChunkUptr(Mix_ChunkPtr chunk) : chunk(std::move(chunk)) {};
	Mix_ChunkPtr chunk;
#endif

public:
#ifdef __EMSCRIPTEN__
	inline ChunkUptr(ChunkUptr&& src) : chunk(src.chunk) { src.chunk = -1; };
	inline ChunkUptr() : chunk(-1) {};
	inline ChunkUptr& operator=(ChunkUptr&& src) { std::swap(chunk, src.chunk); return *this; };
#else
	inline ChunkUptr(ChunkUptr&& src) : chunk(std::move(src.chunk)) {};
	inline ChunkUptr() : chunk(nullptr) {};
	inline ChunkUptr& operator=(ChunkUptr&& u) { std::swap(chunk, u.chunk); return *this; };
#endif
	~ChunkUptr();

#ifdef __EMSCRIPTEN__
	inline ChunkRawPtr get() { return ChunkRawPtr(chunk); };
#else
	inline ChunkRawPtr get() { return ChunkRawPtr(chunk.get()); };
#endif
};

#endif /* SRC_AUDIOSYSTEM_H_ */
