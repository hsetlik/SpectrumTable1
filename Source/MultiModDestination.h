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
#include "PluginProcessor.h"

class DepthSlider : public juce::Slider
{
public:
    DepthSlider(juce::String source, bool isVertical) :
    sourceId(source)
    {
        auto sliderStyle = (isVertical) ? (juce::Slider::LinearVertical) : (juce::Slider::LinearHorizontal);
        setSliderStyle(sliderStyle);
        setRange(-1.0f, 1.0f);
        setValue(0.0f);
        setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    }
    ~DepthSlider() {}
    juce::String sourceId;

    
};

class MultiDepthSlider : public juce::TabbedComponent
{
public:
    //functions
    MultiDepthSlider(juce::String destId, bool isVertical) :
    juce::TabbedComponent( (isVertical) ? juce::TabbedButtonBar::TabsAtRight : juce::TabbedButtonBar::TabsAtBottom),
    parentIsVertical(isVertical)
    {
        tabBkgnd = color.RGBColor(110, 110, 110);
        setTabBarDepth(6);
    }
    void addSource(juce::String sourceId);
    void mouseDown(const juce::MouseEvent &e) override;
    //data
    bool parentIsVertical;
    juce::OwnedArray<juce::String> sourceIds;
    juce::String destId;
    juce::OwnedArray<DepthSlider> depthSliders;
    juce::Colour tabBkgnd;
private:
    ColorCreator color;
};


class MultiModDestination : public juce::DragAndDropTarget, public juce::Component
{
public:
    //functions
    MultiModDestination(juce::String idStr, bool isVertical, float min, float max) :
    destSliderIsVertical(isVertical),
    paramMin(min),
    paramMax(max),
    depthSliderSet(idStr, isVertical),
    destId(idStr)
    {
        addAndMakeVisible(&paramSlider);
        addAndMakeVisible(&depthSliderSet);
        auto sliderStyle = (isVertical) ? (juce::Slider::LinearVertical) : (juce::Slider::LinearHorizontal);
        paramSlider.setSliderStyle(sliderStyle);
        paramSlider.setRange(paramMin, paramMax);
        
    }
    ~MultiModDestination() {}
    void resized() override;
    void paint(juce::Graphics& g) override
    {
        juce::Rectangle<float> area = getLocalBounds().toFloat();
        g.setColour(juce::Colours::darkgrey);
        g.fillRect(paramSlider.getBounds());
        
    }
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
    bool isInterestedInDragSource(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override;
    
    bool shouldDrawDragImageWhenOver() override
    {
        return false;
    }
    
    //data
    MultiDepthSlider depthSliderSet;
    bool destSliderIsVertical;
    float paramMin;
    float paramMax;
    juce::String destId;
    juce::Slider paramSlider;
private:
    ColorCreator color;
};
