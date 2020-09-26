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

class ModDestination  : public juce::Component, public juce::DragAndDropTarget
{
public:
    //functions
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
        ModSourceComponent* newSource = dynamic_cast<ModSourceComponent*>(sourceComponent);
        sources.push_back(newSource);
    }
    void resized() override;
    //data
    int oscIndex;
    juce::String idString;
    juce::DragAndDropContainer* parent;
    std::vector<ModSourceComponent*> sources;
private:
    ColorCreator color;
    juce::Colour ringColor;
    juce::Colour centerColor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModDestination)
};

