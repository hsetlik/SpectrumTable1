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
    addAndMakeVisible(depthSliders.getLast());
}

void ModDestinationSlider::resized()
{
    int n = getWidth() / 24;
    //main slider spans the whole width and is 4n high
    paramSlider.setBounds(0, 0, getWidth(), 4 * n);
    if(depthSliders.size() != 0)
    {
    for(int i = 0 ; i < depthSliders.size(); ++i)
        {
            int newY = (4 * n) + (2 * i * n);
            depthSliders[i]->setBounds(6 * n, newY, 12 * n, 2 * n);
        }
    }
}
