/*
  ==============================================================================

    MultiModDestination.h
    Created: 27 Sep 2020 12:51:10pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ModSourceComponent.h"
class DepthSlider : public juce::Slider
{
public:
    DepthSlider(juce::String source, bool isVertical) :
    sourceId(source)
    {
        auto sliderStyle = (isVertical) ? (juce::Slider::LinearVertical) : (juce::Slider::LinearHorizontal);
        setSliderStyle(sliderStyle);
        setRange(-1.0f, 1.0f);
    }
    ~DepthSlider() {}
    juce::String sourceId;
    
};

class MultiModDestination : public juce::DragAndDropTarget, public juce::TabbedComponent
{
public:
    //functions
    MultiModDestination(juce::String idStr, bool isVertical, float min, float max) :
    juce::TabbedComponent( (isVertical) ? juce::TabbedButtonBar::TabsAtRight : juce::TabbedButtonBar::TabsAtBottom),
    paramMin(min),
    paramMax(max),
    destId(idStr)
    {
        addAndMakeVisible(&paramSlider);
        auto sliderStyle = (isVertical) ? (juce::Slider::LinearVertical) : (juce::Slider::LinearHorizontal);
        paramSlider.setSliderStyle(sliderStyle);
        paramSlider.setRange(paramMin, paramMax);
        
    }
    ~MultiModDestination() {}
    void resized() override;
    void paint(juce::Graphics& g) override;
    //dragdroptarget virtual functions
    void itemDropped(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override;
    void itemDragEnter(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override
    {
    }
    void itemDragExit(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override
    {
    }
    void itemDragMove(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override
    {
    }
    bool isInterestedInDragSource(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override
    {
        return true;
    }
    bool shouldDrawDragImageWhenOver() override
    {
        return false;
    }
    //data
    juce::OwnedArray<juce::String> sourceIds;
    juce::OwnedArray<DepthSlider> depthSliders;
    float paramMin;
    float paramMax;
    juce::String destId;
    juce::Slider paramSlider;
};
