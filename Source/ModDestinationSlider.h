/*
  ==============================================================================

    ModDestinationSlider.h
    Created: 27 Sep 2020 8:29:05am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "RGBColor.h"
#include "ModSourceComponent.h"

class ModDepthSlider : public juce::Slider
{
public:
    //functions
    ModDepthSlider(juce::String modSourceId)
    {
        setSliderStyle(juce::Slider::LinearHorizontal);
        modThumbColor = color.fromRGB(100, 210, 110);
        modTrackColor = color.fromRGB(10, 10, 10);
        setColour(thumbColourId, modThumbColor);
        setColour(trackColourId, modTrackColor);
        setRange(-1.0, 1.0);
        setValue(0.0);
    }
    ~ModDepthSlider() {}
    //data
    juce::String sourceId;
private:
    ColorCreator color;
    juce::Colour modThumbColor;
    juce::Colour modTrackColor;
};


class ModDestinationSlider : public juce::Component, public juce::DragAndDropTarget
{
public:
    enum ModTargetId
    {
        param0,
        param1,
        numHarmonics
    };
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
    void addModSlider(const SourceDetails &dragSourceDetails);
    void resized() override;
    //data
    juce::Slider paramSlider;
    juce::OwnedArray<ModDepthSlider> depthSliders;
    int oscIndex;
    juce::String idString;
    bool hasModulation = false;
};
