//
// Copyright (c) 2017-2018 Jimmy Lord http://www.flatheadgames.com
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "GamePCH.h"

#include "SoundPlayerXAudio.h"

//====================================================================================================
// SoundObject
//====================================================================================================
SoundObject::SoundObject()
{
    m_pFileBuffer = 0;
    m_WaveDesc.valid = false;

    memset( &m_XAudioBuffer, 0, sizeof(XAUDIO2_BUFFER) );
}

SoundObject::~SoundObject()
{
    delete[] m_pFileBuffer;
}

void SoundObject::Init(const char* pFileBuffer, MyWaveDescriptor waveDescriptor)
{
    m_pFileBuffer = pFileBuffer;
    m_WaveDesc = waveDescriptor;

    m_XAudioBuffer.Flags = XAUDIO2_END_OF_STREAM;
    m_XAudioBuffer.AudioBytes = m_WaveDesc.datasize;
    m_XAudioBuffer.pAudioData = (const BYTE*)m_WaveDesc.data;
    m_XAudioBuffer.PlayBegin = 0;
    m_XAudioBuffer.PlayLength = 0;
    m_XAudioBuffer.LoopBegin = 0;
    m_XAudioBuffer.LoopLength = 0;
    m_XAudioBuffer.LoopCount = 0;
    m_XAudioBuffer.pContext = 0;
}

//====================================================================================================
// SoundChannel
//====================================================================================================
SoundChannel::SoundChannel()
{
    m_pSourceVoice = 0;
    m_pVoiceCallback = 0;

    m_CurrentState = SoundChannelState_Free;
    m_TimePlaybackStarted = 0;
}

SoundChannel::~SoundChannel()
{
    delete m_pVoiceCallback;
}

void SoundChannel::PlaySound(SoundObject* pSoundObject)
{
    m_CurrentState = SoundChannelState_Playing;

    m_pSourceVoice->Stop();
	m_pSourceVoice->FlushSourceBuffers();
    m_pSourceVoice->Start();
    m_pSourceVoice->SubmitSourceBuffer( pSoundObject->GetXAudioBuffer() );

    m_TimePlaybackStarted = fw::GetSystemTimeSinceGameStart();
}

void SoundChannel::StopSound()
{
    m_CurrentState = SoundChannelState_Free;

    m_pSourceVoice->Stop();
	m_pSourceVoice->FlushSourceBuffers();

    m_TimePlaybackStarted = 0;
}

//====================================================================================================
// SoundPlayer
//====================================================================================================
SoundPlayer::SoundPlayer()
{
    CoInitializeEx( NULL, COINIT_MULTITHREADED );

    HRESULT result = XAudio2Create( &m_pEngine );
    
    if( result == S_OK )
    {
        result = m_pEngine->CreateMasteringVoice( &m_pMasteringVoice );
    }

    if( result != S_OK )
    {
        fw::OutputMessage( "Error initializing XAudio\n" );
        exit( 1 );
    }

    for( int i=0; i<MAX_CHANNELS; i++ )
    {
        IXAudio2SourceVoice* pSourceVoice;

        // Hardcoded for now, all wav's must be this format
        WAVEFORMATEX waveformat;
        waveformat.wFormatTag = 1;
        waveformat.nChannels = 1;
        waveformat.nSamplesPerSec = 44100;
        waveformat.nAvgBytesPerSec = 88200;
        waveformat.nBlockAlign = 2;
        waveformat.wBitsPerSample = 16;
        waveformat.cbSize = 0;

        m_pChannels[i] = new SoundChannel();

        VoiceCallback* pVoiceCallback = new VoiceCallback( m_pChannels[i] );
        int result = m_pEngine->CreateSourceVoice( &pSourceVoice, &waveformat, 0, XAUDIO2_DEFAULT_FREQ_RATIO, pVoiceCallback );

        if( result != S_OK )
        {
            delete pVoiceCallback;
            fw::OutputMessage( "Unable to create source voice\n" );
        }
        else
        {
            m_pChannels[i]->SetSourceVoice( pSourceVoice, pVoiceCallback );
        }
    }
}

SoundPlayer::~SoundPlayer()
{
    for( int i=0; i<MAX_CHANNELS; i++ )
    {
        delete m_pChannels[i];
    }

    m_pEngine->Release();
    CoUninitialize();
}

SoundObject* SoundPlayer::LoadSound(const char* fullpath)
{
    SoundObject* pSound = new SoundObject();

    long len;
    const char* fileBuffer = fw::LoadCompleteFile( fullpath, &len );
    if( fileBuffer )
    {
        MyWaveDescriptor waveDescriptor = WaveLoader::ParseWaveBuffer( fileBuffer, len );

        if( waveDescriptor.valid == false )
        {
            fw::OutputMessage( "WAV file parsing failed (%s)\n", fullpath );
            delete[] fileBuffer;
        }
        else
        {
            pSound->Init( fileBuffer, waveDescriptor );
        }
    }

    return pSound;
}

int SoundPlayer::PlaySound(SoundObject* pSoundObject)
{
    if( pSoundObject->IsValid() == false )
        return -1; // Sound didn't play

    // Find a free or oldest channel.
    int channelIndex = FindFreeChannel();

    // If no channel was found (should be impossible since we'll also accept oldest channel)
    if( channelIndex == -1 )
        return -1;

    m_pChannels[channelIndex]->PlaySound( pSoundObject );

    // Return the channel used, so the game can pause/resume/stop it.
    return channelIndex;
}

void SoundPlayer::StopSound(int channelIndex)
{
    m_pChannels[channelIndex]->StopSound();
}

int SoundPlayer::FindFreeChannel()
{
    int channelIndex = 0;

    // If all channels are in use, find and use the oldest sound channel
    if( channelIndex == MAX_CHANNELS )
    {
        channelIndex = FindOldestChannel();
    }

    return channelIndex;
}

int SoundPlayer::FindOldestChannel()
{
    int channelIndex = 0;

    return channelIndex;
}
