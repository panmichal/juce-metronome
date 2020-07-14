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
struct MetronomeLookAndFeel : public LookAndFeel_V4
{
    MetronomeLookAndFeel()
    {
        
    }
    
    void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                           float sliderPos, float minSliderPos, float maxSliderPos,
                           const Slider::SliderStyle style, Slider& slider) override
    {
        g.fillAll (slider.findColour (Slider::backgroundColourId));

        if (style == Slider::LinearBar || style == Slider::LinearBarVertical)
        {
            Path p;
            if (style == Slider::LinearBarVertical)
                p.addRectangle ((float) x, sliderPos, (float) width, 1.0f + (float) height - sliderPos);
            else
                p.addRectangle ((float) x, (float) y, sliderPos - (float) x, (float) height);

            auto baseColour = slider.findColour (Slider::rotarySliderFillColourId)
                                    .withMultipliedSaturation (slider.isEnabled() ? 1.0f : 0.5f)
                                    .withMultipliedAlpha (0.8f);

            g.setColour (baseColour);
            g.fillPath (p);

            auto lineThickness = jmin (15.0f, (float) jmin (width, height) * 0.45f) * 0.1f;
            g.drawRect (slider.getLocalBounds().toFloat(), lineThickness);
        }
        else
        {
            drawLinearSliderBackground (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
//            drawLinearSliderThumb      (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
            Path p;
//            p.addRectangle ((float) x, (float) y, sliderPos - (float) x, (float) height);
            p.addEllipse(sliderPos - (float) x + 7.5, (float) y + (height / 2) - 7.5, 15.0, 15.0);
            g.setColour(Colours::red);
            g.fillPath (p);
            
        }
    }
    
    void drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height,
                                     float /*sliderPos*/,
                                     float /*minSliderPos*/,
                                     float /*maxSliderPos*/,
                                     const Slider::SliderStyle /*style*/, Slider& slider) override
    {
        auto sliderRadius = (float) getSliderThumbRadius (slider) - 5.0f;
        Path on, off;

        if (slider.isHorizontal())
        {
            auto iy = (float) y + (float) height * 0.5f - sliderRadius * 0.5f;
            Rectangle<float> r ((float) x - sliderRadius * 0.5f, iy, (float) width + sliderRadius, sliderRadius);
            auto onW = r.getWidth() * ((float) slider.valueToProportionOfLength (slider.getValue()));

            on.addRectangle (r.removeFromLeft (onW));
            off.addRectangle (r);
        }
        else
        {
            auto ix = (float) x + (float) width * 0.5f - sliderRadius * 0.5f;
            Rectangle<float> r (ix, (float) y - sliderRadius * 0.5f, sliderRadius, (float) height + sliderRadius);
            auto onH = r.getHeight() * ((float) slider.valueToProportionOfLength (slider.getValue()));

            on.addRectangle (r.removeFromBottom (onH));
            off.addRectangle (r);
        }

        g.setColour (slider.findColour (Slider::rotarySliderFillColourId));
        g.fillPath (on);

        g.setColour (slider.findColour (Slider::trackColourId));
        g.fillPath (off);
    }
};

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
    float level = 1.0;
    
    PlayState mPlayState { PlayState::Stopped };
    
    Metronome mMetronome;
    MetronomeLookAndFeel lookAndFeel;
    
    FlexBox metronomeBox;
    FlexBox settingsBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
