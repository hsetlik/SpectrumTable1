/*
  ==============================================================================

    EnvelopeSliderSet.h
    Created: 24 Sep 2020 6:16:13pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class EnvelopeSliderSet  : public juce::Component
{
public:
    EnvelopeSliderSet(int index);
    ~EnvelopeSliderSet() override;
    void resized() override;
    juce::Slider aSlider;
    juce::Slider dSlider;
    juce::Slider sSlider;
    juce::Slider rSlider;
private:
    int oscIndex;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeSliderSet)
};
