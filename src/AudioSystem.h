#ifndef SRC_AUDIOSYSTEM_H_
#define SRC_AUDIOSYSTEM_H_

typedef int AudioMusic;
typedef int AudioChunk;

#ifndef __EMSCRIPTEN__
	#include <vector>
	#include "SDLUtils.h"
#endif


class AudioSystem {
private:
#ifndef __EMSCRIPTEN__
	std::vector<Mix_MusicPtr> musics;
	std::vector<Mix_ChunkPtr> chunks;
#endif
public:
	AudioSystem();
	virtual ~AudioSystem();

	AudioMusic loadMusic(const char* filepath);
	AudioChunk loadChunk(const char* filepath);
	void playMusic(AudioMusic music);
	void stopMusic();
	void playChunk(AudioChunk chunk);
	void setMusicVolume(float volume);
	void setChunkVolume(float volume);
};

#endif /* SRC_AUDIOSYSTEM_H_ */
