/*
  ==============================================================================

    DecibelSlider.h
    Created: 25 Jun 2020 9:06:14pm
    Author:  Michał Strzelczyk

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DecibelSlider : public Slider
{
public:
    DecibelSlider() { };
    
    double getValueFromText(const String& text) override;
    String getTextFromValue(double value) override;
};
