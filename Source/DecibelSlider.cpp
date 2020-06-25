/*
  ==============================================================================

    DecibelSlider.cpp
    Created: 25 Jun 2020 9:06:14pm
    Author:  Michał Strzelczyk

  ==============================================================================
*/

#include "DecibelSlider.h"

double DecibelSlider::getValueFromText(const String& text)
{
    auto minusInfinitydB = -100.0;
    auto decibelText = text.upToFirstOccurrenceOf("dB", false, false);
    
    return decibelText.equalsIgnoreCase("-INF") ? minusInfinitydB : decibelText.getDoubleValue();
}

String DecibelSlider::getTextFromValue(double value)
{
    return Decibels::toString(value);
}
