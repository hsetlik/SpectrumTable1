/*
  ==============================================================================

    ModSourceComponent.h
    Created: 25 Sep 2020 11:25:38am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ModSourceComponent  : public juce::Component //any modulation source components (LFOs, Envelopes, Noise, etc.) need to include an instance of this class
{
public:
    ModSourceComponent(juce::String desc, juce::DragAndDropContainer* parentContainer);
    ~ModSourceComponent() {}
    void mouseDown(const juce::MouseEvent& e) override
    {
        parent->startDragging(description, this);
    }
    void paint (juce::Graphics&) override;
    void resized() override;
    void changeCenterColor(juce::Colour newColor)
    {
        centerColor = newColor;
    }
    void updateValue(float newValue)
    {
        paramValue = newValue;
    }
    float getValue()
    {
        return paramValue;
    }
    juce::DragAndDropContainer* parent;
    juce::String description;
private:
    float paramValue = 0.0f;
    juce::Colour ringColor = juce::Colours::black;
    juce::Colour centerColor = juce::Colours::skyblue;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModSourceComponent)
};
