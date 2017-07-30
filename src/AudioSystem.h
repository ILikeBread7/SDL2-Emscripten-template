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

#endif

class MusicRawPtr;
class MusicUptr;
class ChunkRawPtr;
class ChunkUptr;

class AudioSystem {
public:
	AudioSystem();
	virtual ~AudioSystem();

	MusicUptr loadMusic(const char* filepath);
	ChunkUptr loadChunk(const char* filepath);
	void playMusic(MusicRawPtr music);
	void stopMusic();
	void playChunk(ChunkRawPtr chunk);
	void setMusicVolume(float volume);
	void setChunkVolume(float volume);
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
	MusicUptr(const MusicUptr&) = delete;
#ifdef __EMSCRIPTEN__
	inline MusicUptr(int music) : music(music) {};
	int music;
#else
	inline MusicUptr(Mix_MusicPtr music) : music(std::move(music)) {};
	Mix_MusicPtr music;
#endif

public:
#ifdef __EMSCRIPTEN__
	inline MusicUptr(MusicUptr&& src) : music(src.music) { src.music = -1; };
	inline MusicUptr& operator=(MusicUptr&& u) { music = u.music; u.music = -1; return *this; };
	inline MusicUptr() : music(-1) {};
#else
	inline MusicUptr(MusicUptr&& src) : music(std::move(src.music)) {};
	inline MusicUptr& operator=(MusicUptr&& u) { music = std::move(u.music); return *this; };
	inline MusicUptr() : music(nullptr) {};
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
	inline ChunkUptr& operator=(ChunkUptr&& u) { chunk = u.chunk; u.chunk = -1; return *this; };
	inline ChunkUptr() : chunk(-1) {};
#else
	inline ChunkUptr(ChunkUptr&& src) : chunk(std::move(src.chunk)) {};
	inline ChunkUptr& operator=(ChunkUptr&& u) { chunk = std::move(u.chunk); return *this; };
	inline ChunkUptr() : chunk(nullptr) {};
#endif
	~ChunkUptr();

#ifdef __EMSCRIPTEN__
	inline ChunkRawPtr get() { return ChunkRawPtr(chunk); };
#else
	inline ChunkRawPtr get() { return ChunkRawPtr(chunk.get()); };
#endif
};

#endif /* SRC_AUDIOSYSTEM_H_ */
