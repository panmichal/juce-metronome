/*
  ==============================================================================

    Metronome.h
    Created: 17 Jun 2020 9:37:07pm
    Author:  Michał Strzelczyk

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Metronome : public HighResolutionTimer
{
public:
    Metronome();
    
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill, const float& gain);
    void reset();
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    
    void hiResTimerCallback() override;
    
    int mBpm = { 120 };
    float mGain = { 1.0 };
    
private:
    int mTotalSamples { 0 };
    double mSampleRate { 0 };
    int mInterval { 0 };
    int mSamplesRemaining;
    
    AudioFormatManager mFormatManager;
    std::unique_ptr<AudioFormatReaderSource> pMetronomeSample { nullptr };
};
