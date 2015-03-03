#include "SoundManager.h"
#include "Log.h"

SoundManager::SoundManager()
{
    Mix_OpenAudio(SOUND_FREQUENCY, SOUND_FORMAT, SOUND_CHANNELS, SOUND_CHUNKSIZE);
}

SoundManager &SoundManager::instance()
{
    static SoundManager m_instance;
    return m_instance;
}

bool SoundManager::loadSound(std::string keyName, std::string fileName, audio_type type) {
    if(type == SOUND_SFX)
    {
        Mix_Chunk *chunk = Mix_LoadWAV(fileName.c_str());
        if(chunk == 0) {
            Log::Error("Failed to load SFX :  " + fileName);
            Log::Error(Mix_GetError());
            return false;
        }
        else {
            m_soundbuffers[keyName] = chunk;
            return true;
        }
    }

    else if(type == SOUND_MUSIC)
    {
        Mix_Music *chunk = Mix_LoadMUS(fileName.c_str());
        if(chunk == 0) {
            Log::Error("Failed to load Music :  " + fileName);
            Log::Error(Mix_GetError());
            return false;
        }
        else {
            m_musicbuffers[keyName] = chunk;
            return true;
        }
    }

    else {
        Log::Error("Failed to load invalid file type " + fileName);
        return false;
    }

}

void SoundManager::playSound(std::string keyName, bool loop) {

}

void SoundManager::playMusic(std::string keyName, bool loop) {

}
