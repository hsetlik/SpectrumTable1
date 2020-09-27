/*
  ==============================================================================

    MultiModDestination.cpp
    Created: 27 Sep 2020 12:51:10pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "MultiModDestination.h"

void MultiDepthSlider::addSource(juce::String sourceId)
{
    depthSliders.add(new DepthSlider(sourceId, parentIsVertical));
    addTab(sourceId + "tab", tabBkgnd, depthSliders.getLast(), false);
}

void MultiDepthSlider::mouseDown(const juce::MouseEvent &e)
{
    if(e.mods.isRightButtonDown())
    {
        printf("right click\n");
        removeTab(getCurrentTabIndex());
    }
}
void MultiModDestination::itemDropped(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails)
{
    if(isInterestedInDragSource(dragSourceDetails))
    {
        juce::Component* sourceComponent = dragSourceDetails.sourceComponent.get();
        ModSourceComponent* newSource = dynamic_cast<ModSourceComponent*>(sourceComponent);
        juce::String sourceId = newSource->description;
        depthSliderSet.addSource(sourceId);
    }
}
bool MultiModDestination::isInterestedInDragSource(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails)
{
    juce::Component* sourceComponent = dragSourceDetails.sourceComponent.get();
    ModSourceComponent* newSource = dynamic_cast<ModSourceComponent*>(sourceComponent);
    juce::String newSourceId = newSource->description;
    for(int i = 0; i < depthSliderSet.sourceIds.size(); ++i)
    {
        if(newSourceId == *depthSliderSet.sourceIds[i])
        {
            return false;
        }
    }
    return true;
}

void MultiModDestination::resized()
{
    int longDim;
    destSliderIsVertical ? (longDim = getHeight()) : (longDim = getWidth());
    int n = longDim / 16;
    if(destSliderIsVertical)
    {
        paramSlider.setBounds(0, 0, 2.5 * n, 10 * n);
        depthSliderSet.setBounds(0, 10 * n, 1.5 * n, 8 * n);
    }
    else
    {
        paramSlider.setBounds(0, 0, 10 * n, 2.5 * n);
        depthSliderSet.setBounds(0, 2.5 * n, 8 * n, 1.5 * n);
    }
    
}
