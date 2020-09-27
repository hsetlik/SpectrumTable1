/*
  ==============================================================================

    ModDestinationSlider.cpp
    Created: 27 Sep 2020 8:29:05am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "ModDestinationSlider.h"

ModDestinationSlider::ModDestinationSlider(ModTargetId id, int index, juce::Slider::SliderStyle style) : oscIndex(index), idString(id)
{
    setSliderStyle(style);
    
    
}
