/*
  ==============================================================================

    MultiModDestination.cpp
    Created: 27 Sep 2020 12:51:10pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "MultiModDestination.h"
void MultiModDestination::itemDropped(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails)
{
    juce::Component* sourceComponent = dragSourceDetails.sourceComponent.get();
    ModSourceComponent* newSource = dynamic_cast<ModSourceComponent*>(sourceComponent);
    juce::String sourceId = newSource->description;
}
