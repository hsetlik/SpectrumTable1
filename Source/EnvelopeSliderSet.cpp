/*
  ==============================================================================

    EnvelopeSliderSet.cpp
    Created: 24 Sep 2020 6:16:13pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EnvelopeSliderSet.h"

//==============================================================================
EnvelopeSliderSet::EnvelopeSliderSet(int index) : oscIndex(index)
{
    addAndMakeVisible(aSlider);
    aSlider.setRange(1.0f, 15000.0f);
    aSlider.setSliderStyle(juce::Slider::Rotary);
    aSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    aSlider.setNumDecimalPlacesToDisplay(0);
    
    addAndMakeVisible(dSlider);
    dSlider.setRange(1.0f, 15000.0f);
    dSlider.setSliderStyle(juce::Slider::Rotary);
    dSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    dSlider.setNumDecimalPlacesToDisplay(0);
    
    addAndMakeVisible(sSlider);
    sSlider.setRange(0.0f, 1.0f);
    sSlider.setSliderStyle(juce::Slider::Rotary);
    sSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    sSlider.setNumDecimalPlacesToDisplay(2);
    
    addAndMakeVisible(rSlider);
    rSlider.setRange(1.0f, 15000.0f);
    rSlider.setSliderStyle(juce::Slider::Rotary);
    rSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    rSlider.setNumDecimalPlacesToDisplay(0);
}

EnvelopeSliderSet::~EnvelopeSliderSet()
{
}


void EnvelopeSliderSet::resized()
{
    int n = getWidth() / 20;
    aSlider.setBounds(n, n, 3 * n, 3 * n);
    dSlider.setBounds(6 * n, n, 3 * n, 3 * n);
    sSlider.setBounds(11 * n, n, 3 * n, 3 * n);
    rSlider.setBounds(16 * n, n, 3 * n, 3 * n);
}
