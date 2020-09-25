/*
  ==============================================================================

    LFOComponent.cpp
    Created: 25 Sep 2020 10:14:55am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LFOComponent.h"

//==============================================================================
LFOComponent::LFOComponent()
{
    addAndMakeVisible(&frequencySlider);
    frequencySlider.setSliderStyle(juce::Slider::Rotary);
    frequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    frequencySlider.setRange(0.01f, 20.0f);
    
    
    addAndMakeVisible(&waveformChoice);
    waveformChoice.addItem("Sine Wave", 1);
    waveformChoice.addItem("Square Wave", 2);
    waveformChoice.addItem("Triangle Wave", 3);
    waveformChoice.addItem("Sawtooth Wave", 4);

}

LFOComponent::~LFOComponent()
{
}

void LFOComponent::resized()
{
    int n = getWidth() / 10;
    waveformChoice.setBounds(n, n, 6 * n, n);
    frequencySlider.setBounds(3 * n, 3 * n, 4 * n, 4 * n);
}

void LFOComponent::attachLfoToTree(juce::AudioProcessorValueTreeState *target)
{
   lfoWaveShapeAttach.reset(new juce::AudioProcessorValueTreeState::ComboBoxAttachment(*target, "lfoWaveParam", waveformChoice));
    lfoFreqAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*target, "lfoFreqParam", frequencySlider));
}


juce::AudioProcessorParameterGroup LFOComponent::createLFOParamGroup()
{
    juce::AudioProcessorParameterGroup group;
    group.addChild(std::make_unique<juce::AudioParameterFloat>("lfoFreqParam", "LFO Frequency", 0.01f, 20.0f, 1.0f));
    juce::StringArray strArray;
    strArray.add("Sine Wave");
    strArray.add("Square Wave");
    strArray.add("Triangle Wave");
    strArray.add("Saw Wave");
    group.addChild(std::make_unique<juce::AudioParameterChoice>("lfoWaveParam", "LFO Wave Shape", strArray, 1));
    return group;
}
