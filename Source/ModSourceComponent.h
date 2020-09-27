/*
  ==============================================================================

    ModSourceComponent.h
    Created: 27 Sep 2020 9:22:36am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ModSourceComponent : public juce::Component
{
public:
    ModSourceComponent(juce::String idString) : sourceId(idString)
    {
        
    }
    ~ModSourceComponent() {}
    juce::String sourceId;
    
};
