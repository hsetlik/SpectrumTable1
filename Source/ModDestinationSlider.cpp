/*
  ==============================================================================

    ModDestinationSlider.cpp
    Created: 27 Sep 2020 8:29:05am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "ModDestinationSlider.h"

ModDestinationSlider::ModDestinationSlider(ModTargetId id, int index, juce::Slider::SliderStyle style) : oscIndex(index), idString(id)
{
    paramSlider.setSliderStyle(style);
    
    
}

void ModDestinationSlider::itemDropped(const SourceDetails &dragSourceDetails)
{
    addModSlider(dragSourceDetails);
}

void ModDestinationSlider::addModSlider(const SourceDetails &dragSourceDetails)
{
    juce::String newSourceId;
    juce::Component* comp = dragSourceDetails.sourceComponent.get();
    ModSourceComponent* modComp = dynamic_cast<ModSourceComponent*>(comp);
    newSourceId = modComp->sourceId;
    
    depthSliders.add(new ModDepthSlider(newSourceId));
}
