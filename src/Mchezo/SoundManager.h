#ifndef _SOUNDMANAGER_H_
#define _SOUNDMANAGER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <map>
#include "Defines.h"


enum audio_type
{
    SOUND_MUSIC = 0,
    SOUND_SFX = 1
};

class SoundManager
{
public:

    static SoundManager &instance();

    bool loadSound(std::string keyName, std::string fileName, audio_type type);

    void playSound(std::string keyName, int loop);

    void playMusic(std::string keyName, int loop);


private:
    SoundManager();

    ~SoundManager();

    SoundManager(const SoundManager &)
    { }

    SoundManager &operator=(const SoundManager &)
    { }

    std::map<std::string, Mix_Chunk *> m_soundbuffers;
    std::map<std::string, Mix_Music *> m_musicbuffers;
};

#endif //SOUNDMANAGER_H_