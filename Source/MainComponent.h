/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Metronome.h"
#include "DecibelSlider.h"
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
    
    void play();
    void stop();
    
    enum class PlayState
    {
        Playing,
        Stopped
    };

private:
    TextButton playButton { "Play" };
    TextButton stopButton { "Stop" };
    TextEditor bpmField { "BPM" };
    
    DecibelSlider decibelSlider;
    Label decibelLabel;
    float level = 0.0f;
    
    PlayState mPlayState { PlayState::Stopped };
    
    Metronome mMetronome;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
