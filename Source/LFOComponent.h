/*
  ==============================================================================

    LFOComponent.h
    Created: 25 Sep 2020 10:14:55am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "maximilian.h"

//==============================================================================
/*
*/
class LFOComponent  : public juce::Component
{
public:
    enum waveShape
    {
        sine,
        square,
        triangle,
        saw
    };
    LFOComponent();
    ~LFOComponent() override;
    void resized() override;
    void attachLfoToTree(juce::AudioProcessorValueTreeState* target);
    juce::AudioProcessorParameterGroup createLFOParamGroup();
    juce::ComboBox waveformChoice;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> lfoWaveShapeAttach;
    juce::Slider frequencySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lfoFreqAttach;
private:
    float frequency = 0.3f;
    waveShape currentWaveType = sine;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOComponent)
};
