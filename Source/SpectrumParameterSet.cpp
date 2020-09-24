/*
  ==============================================================================

    SpectrumParameterSet.cpp
    Created: 22 Sep 2020 12:06:10pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SpectrumParameterSet.h"

//==============================================================================
SpectrumParameterSet::SpectrumParameterSet()
{
    addAndMakeVisible(&nSlider);
    addAndMakeVisible(&p0Slider);
    addAndMakeVisible(&p1Slider);
    addAndMakeVisible(&algButton);
    algButton.setButtonText("Algorithm");
    algButton.setClickingTogglesState(true);

    nSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    p0Slider.setSliderStyle(juce::Slider::LinearHorizontal);
    p1Slider.setSliderStyle(juce::Slider::LinearHorizontal);
    
    nSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 50, 20);
    p0Slider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 50, 20);
    p1Slider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 50, 20);
    
    nSlider.setRange(1.0f, 40.0f);
    p0Slider.setRange(0.0f, 15.0f);
    p1Slider.setRange(1.0f, 15.0f);
    
    nSlider.setValue(1.0f);
    p0Slider.setValue(1.0f);
    p1Slider.setValue(1.0f);
}

SpectrumParameterSet::~SpectrumParameterSet()
{
}

void SpectrumParameterSet::attachToTree(juce::AudioProcessorValueTreeState* pTree)
{
    nAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "nParam",
                                                                                  nSlider));
    p0Attach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "p0Param",
                                                                                  p0Slider));
    p1Attach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "p1Param",
                                                                                  p1Slider));
    algAttach.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(*pTree, "algParam",
                                                                                  algButton));
}
void SpectrumParameterSet::paint (juce::Graphics& g)
{
    

}

void SpectrumParameterSet::resized()
{
    int l = getWidth() / 15;
    nSlider.setBounds(l, l, 10 * l, l);
    p0Slider.setBounds(l, 3 * l, 10 * l, l);
    p1Slider.setBounds(l, 5 * l, 10 * l, l);
    algButton.setBounds(l, 7 * l, 4 * l, l);
    

}
