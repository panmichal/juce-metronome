/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    playButton.setToggleState(false, NotificationType::dontSendNotification);
    playButton.setRadioGroupId(1);
    playButton.onClick = [this]() { play(); };
    addAndMakeVisible(playButton);
    stopButton.setToggleState(true, NotificationType::dontSendNotification);
    stopButton.setRadioGroupId(1);
    stopButton.onClick = [this]() { stop(); };
    addAndMakeVisible(stopButton);
    
    bpmField.setMultiLine(false);
    bpmField.setText(std::to_string(mMetronome.mBpm));
    bpmField.setInputRestrictions(3, "0123456789");
    bpmField.onTextChange = [this] { mMetronome.mBpm = bpmField.getText().getIntValue(); };
    addAndMakeVisible(bpmField);
    
    decibelSlider.setRange (-100, -12);
    decibelSlider.setTextBoxStyle (Slider::TextBoxRight, false, 100, 20);
    decibelSlider.onValueChange = [this] { level = Decibels::decibelsToGain ((float) decibelSlider.getValue()); };
    decibelSlider.setValue (Decibels::gainToDecibels (level));
    decibelLabel.setText ("Metronome gain in dB", NotificationType::dontSendNotification);
    
    addAndMakeVisible (decibelSlider);
    addAndMakeVisible (decibelLabel);
    
    
    setSize(500, 400);
    

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    mMetronome.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
    
    if (mPlayState == PlayState::Playing)
    {
        mMetronome.getNextAudioBlock(bufferToFill, level);
    } else
    {
        
    }
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    Rectangle<int> bounds = getLocalBounds();
    
    
    FlexBox metronomeBox;
    metronomeBox.alignContent = FlexBox::AlignContent::center;
    metronomeBox.flexWrap = FlexBox::Wrap::wrap;
    metronomeBox.flexDirection = FlexBox::Direction::column;
    metronomeBox.items.add(FlexItem(300, 50, playButton));
    metronomeBox.items.add(FlexItem(300, 50, stopButton));
    metronomeBox.items.add(FlexItem(300, 50, bpmField));
    metronomeBox.performLayout(bounds.removeFromTop(300));
    
    FlexBox settingsBox;
    settingsBox.flexDirection = FlexBox::Direction::column;
    settingsBox.alignContent = FlexBox::AlignContent::center;
    settingsBox.items.add(FlexItem(300, 50, decibelSlider));
                               
    settingsBox.performLayout(bounds);
}

void MainComponent::play()
{
    mPlayState = PlayState::Playing;
}

void MainComponent::stop()
{
    mPlayState = PlayState::Stopped;
    mMetronome.reset();
}
