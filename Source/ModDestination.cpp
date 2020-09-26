/*
  ==============================================================================

    ModDestination.cpp
    Created: 25 Sep 2020 1:05:12pm
    Author:  Hayden Setlik

  ==============================================================================
*/
#include "ModDestination.h"

//==============================================================================

ModDestination::ModDestination(juce::DragAndDropContainer* parentContainer, juce::String idStr, int index) : oscIndex(index), idString(idStr), parent(parentContainer)
{
    ringColor = color.RGBColor(210, 210, 210);
    centerColor = color.RGBColor(100, 100, 100);
    emptyColor = centerColor;
}

void ModDestination::paint (juce::Graphics& g)
{
    juce::Rectangle<float> area = getLocalBounds().toFloat();
    g.setColour(ringColor);
    g.fillEllipse(area);
    g.setColour(centerColor);
    g.fillEllipse(area.reduced(5.0));
}


ModDestinationSlider::ModDestinationSlider(juce::DragAndDropContainer* parentContainer, juce::String idStr, int index) : destination(parentContainer, idStr, index)
{
    addAndMakeVisible(&destination);
    destination.setAlwaysOnTop(true);
    addAndMakeVisible(&depthSlider);
    
    depthSlider.setSliderStyle(juce::Slider::Rotary);
    depthSlider.setRange(0.0f, 1.0f);
    depthSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
}

