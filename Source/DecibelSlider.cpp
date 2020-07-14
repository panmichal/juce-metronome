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
    if (decibelText.equalsIgnoreCase("-INF"))
    {
        return minusInfinitydB;
    } else if (decibelText.equalsIgnoreCase("+0.00"))
    {
        return 0.0;
    } else
    {
        return decibelText.getDoubleValue();
    }
}

String DecibelSlider::getTextFromValue(double value)
{
    if (value == 0)
    {
        return "0 dB";
    }
    return Decibels::toString(value);
}
