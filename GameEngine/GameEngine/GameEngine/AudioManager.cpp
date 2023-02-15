#include "AudioManager.h"

AudioManager::~AudioManager()
{
    clear();
    delete dxtkAudio;
}

void AudioManager::musicPause(int trackNo)
{
    dxtkAudio->musicPause(trackNo);
}

void AudioManager::musicResume(int trackNo)
{
    dxtkAudio->musicResume(trackNo);
}

AudioManager::AudioManager()
{
    dxtkAudio = new audio::DXTKAudio;
    
    //AudioSpace::sound::load(MY_BGM, L"./Data/Audio/WaveBank.xwb", 0.5f);
    //music::load(MY_TITLE, L"./Data/Asset/Musics/title.wav", 0.5f);
    //music::load(MY_TUTO, L"./Data/Asset/Musics/tuto.wav", 0.5f);
}
void AudioManager::Init()
{

    //loadMusic(GAMEBGM, L"./Data/Asset/Musics/game.wav", 0.5f);
    //loadMusic(MAINBGM, L"./Data/Asset/Musics/title.wav", 0.5f);
    //loadEffect(EFFECT, L"./Data/Audio/effect.xwb", 0.5f);
    
    //loadMusic(GAMEBGM, L"./Data/Asset/Musics/gameBGM.wav", 0);
    //loadMusic(MAINBGM, L"./Data/Asset/Musics/mainBGM.wav", 0);
    //loadMusic(WINGAME, L"./Data/Asset/Musics/win.wav", 0);
    //loadMusic(CHARRUN, L"./Data/Asset/Sounds/run.wav", 0.3f);
    //loadMusic(CHARWALK, L"./Data/Asset/Sounds/walk.wav", 0.3f);


    //loadEffect(EFFECT_1, L"./Data/Asset/Sounds/this.xwb", 0.5f);
    

}

void AudioManager::loadEffect(int xwbNo, const wchar_t* xwbFileName, float volume)
{
    dxtkAudio->soundLoad(xwbNo, xwbFileName, volume);
}

void AudioManager::play(int xwbNo, int trackNo)
{
    // XWB‚ª“Ç‚Ýž‚Ü‚ê‚Ä‚¢‚È‚¯‚ê‚ÎƒŠƒ^[ƒ“
    if (!dxtkAudio->xwbIsInUse(xwbNo))
    {
        assert(!"xwb‚ª“Ç‚Ýž‚Ü‚ê‚Ä‚¢‚È‚¢");
        return;
    }

    dxtkAudio->soundPlay(xwbNo, trackNo);
}

void AudioManager::update()
{
    dxtkAudio->update();
}


void AudioManager::loadMusic(int trackNo, const wchar_t* waveFileName, float volume)
{
    dxtkAudio->musicLoad(trackNo, waveFileName, volume);
}


void AudioManager::playMusic(int trackNo, bool isLoop)
{
    dxtkAudio->musicPlay(trackNo, isLoop);
}


void AudioManager::stopAll()
{
    for (int i = 0; i < MUSIC_FILE_MAX; i++)
    {
        stop(i);
    }
}


void AudioManager::stop(int trackNo)
{
    dxtkAudio->musicStop(trackNo);
}