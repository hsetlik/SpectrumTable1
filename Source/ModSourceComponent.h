/*
  ==============================================================================

    ModSourceComponent.h
    Created: 25 Sep 2020 11:25:38am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "maximilian.h"
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


class LfoComponent : public juce::Component
{
public:
    LfoComponent(juce::String desc, juce::DragAndDropContainer* parentContainer, int index);
    ~LfoComponent() {}
    void resized() override;
    
    void attachToTree(juce::AudioProcessorValueTreeState* target)
    {
        juce::String iStr = juce::String(LfoIndex);
        auto pId = "lfoParam"+ iStr;
        freqAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*target, pId, freqSlider));
    }
    juce::AudioProcessorParameterGroup createParamGroup()
    {
        auto groupId = "lfo" + juce::String(LfoIndex);
        auto groupName = "Lfo " + juce::String(LfoIndex);
        juce::AudioProcessorParameterGroup group(groupId, groupName, "|");
        auto paramId = "lfoParam" + juce::String(LfoIndex);
        auto paramName = "LFO " + juce::String(LfoIndex) + " frequency";
        group.addChild(std::make_unique<juce::AudioParameterFloat>(paramId, paramName, 0.01f, 20.0f, 1.0f));
        return group;
    }
    ModSourceComponent modSource;
    int LfoIndex;
    juce::Slider freqSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freqAttach;
    
};
