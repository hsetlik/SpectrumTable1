/*
  ==============================================================================

    ModParentComponent.cpp
    Created: 25 Sep 2020 11:26:11am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ModParentComponent.h"

//==============================================================================

ModParentComponent::~ModParentComponent()
{
}

void ModParentComponent::paint (juce::Graphics& g)
{
   
}

void ModParentComponent::resized()
{
    int n = getHeight() / 24;
    oscSet.setBounds(0, 0, getWidth(),18 * n);
    lfo0.setBounds(0, 18 * n, 4 * n, 6 * n);
}
