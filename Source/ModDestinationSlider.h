/*
  ==============================================================================

    ModDestinationSlider.h
    Created: 27 Sep 2020 8:29:05am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
enum ModTargetId
{
    param0,
    param1,
    numHarmonics
};

class ModDestinationSlider : public juce::Slider, public juce::DragAndDropTarget
{
    //functions
    ModDestinationSlider(ModTargetId target, int oscIndex, juce::Slider::SliderStyle style);
    bool isInterestedInDragSource (const SourceDetails &dragSourceDetails) override
    {
        return true;
    }
    void itemDragEnter (const SourceDetails &dragSourceDetails) override
    {
    }
    void itemDragMove(const SourceDetails &dragSourceDetails) override
    {
    }
    void itemDragExit (const SourceDetails &dragSourceDetails) override
    {
    }
    void itemDropped(const SourceDetails &dragSourceDetails) override;
    bool shouldDrawDragImageWhenOver () override
    {
        return true;
    }
    //data
    int oscIndex;
    juce::String idString;
    bool hasModulation = false;
};
