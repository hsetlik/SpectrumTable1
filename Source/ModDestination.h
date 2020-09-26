/*
  ==============================================================================

    ModDestination.h
    Created: 25 Sep 2020 1:05:12pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include "ModSourceComponent.h"

//==============================================================================
/*
*/

class ModDestination  : public juce::Component, public juce::DragAndDropTarget //make a subclass of this for each type of Modulation
{
public:
    ModDestination(juce::DragAndDropContainer* parentContainer, juce::String idStr, int index);
    ~ModDestination() {}
    void paint (juce::Graphics&) override;
    void setColors(juce::Colour ring, juce::Colour center)
    {
        ringColor = ring;
        centerColor = center;
    }
    void setCenterColor(juce::Colour newCenter)
    {
        centerColor = newCenter;
    }
    void itemDropped(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override
    {
        juce::Component* sourceComponent = dragSourceDetails.sourceComponent.get();
        sources.push_back(sourceComponent);
    }
    int oscIndex;
    juce::String idString;
    juce::DragAndDropContainer* parent;
    std::vector<juce::Component*> sources;
private:
    ColorCreator color;
    juce::Colour ringColor;
    juce::Colour centerColor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModDestination)
};

class ModDestinationSlider : public ModDestination
{
public:
    ModDestinationSlider(juce::DragAndDropContainer* parentContainer, juce::String idStr, int index) :
    ModDestination(parentContainer, idStr, index)
    {
        addAndMakeVisible(&depthSlider);
        depthSlider.setSliderStyle(juce::Slider::Rotary);
        depthSlider.setRange(0.0f, 1.0f);
        depthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    }
    ~ModDestinationSlider() {}
    juce::Slider depthSlider;
};
