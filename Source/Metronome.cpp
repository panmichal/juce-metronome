/*
  ==============================================================================

    Metronome.cpp
    Created: 17 Jun 2020 9:37:07pm
    Author:  Michał Strzelczyk

  ==============================================================================
*/

#include "Metronome.h"

Metronome::Metronome()
{
    mFormatManager.registerBasicFormats();
    File myFile { File::getSpecialLocation(File::SpecialLocationType::userDesktopDirectory)};
    auto mySamples = myFile.findChildFiles(File::TypesOfFileToFind::findFiles, true, "metronome.wav");
//
    jassert(mySamples[0].exists());
    
    auto formatReader = mFormatManager.createReaderFor(mySamples[0]);
//
    pMetronomeSample.reset(new AudioFormatReaderSource(formatReader, true)) ;
}

void Metronome::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill, const double& gain)
{
    const auto bufferSize = bufferToFill.numSamples;
    mTotalSamples += bufferSize;
    DBG("BPM " << mBpm);
    if (mTotalSamples >= mInterval)
    {
        const auto timeToStartPlaying = mTotalSamples - mInterval;
        pMetronomeSample->setNextReadPosition(0);
        
        DBG(timeToStartPlaying);
        for (auto sample = 0; sample < bufferSize; sample++)
        {
            if (sample == timeToStartPlaying)
            {
                pMetronomeSample->getNextAudioBlock(bufferToFill);
            }
        }
        mTotalSamples = mTotalSamples % mInterval;
        
    }
    
    if (pMetronomeSample->getNextReadPosition() != 0)
    {
        pMetronomeSample->getNextAudioBlock(bufferToFill);
    }
}

void Metronome::reset()
{
    mTotalSamples = 0;
}

void Metronome::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    mSampleRate = sampleRate;
    mInterval = 60.0 / mBpm * mSampleRate;
    HighResolutionTimer::startTimer(60);
    
    if (pMetronomeSample != nullptr)
    {
        pMetronomeSample->prepareToPlay(samplesPerBlockExpected, sampleRate);
        DBG("File loaded");
    }
}

void Metronome::hiResTimerCallback()
{
    mInterval = 60.0 / mBpm * mSampleRate;
}
