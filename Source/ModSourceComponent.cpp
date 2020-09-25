/*
  ==============================================================================

    ModSourceComponent.cpp
    Created: 25 Sep 2020 11:25:38am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ModSourceComponent.h"

//==============================================================================
ModSourceComponent::ModSourceComponent(juce::String desc, juce::DragAndDropContainer* parentContainer) :  parent(parentContainer), description(desc)
{
    

}

void ModSourceComponent::paint (juce::Graphics& g)
{
    juce::Rectangle<float> area = getLocalBounds().toFloat();
    g.setColour(ringColor);
    g.fillEllipse(area);
    g.setColour(centerColor);
    g.fillEllipse(area.reduced(5.0));
}

void ModSourceComponent::resized()
{
    juce::Rectangle<int> area = getLocalBounds();
    setBounds(area);
}
