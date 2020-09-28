/*
  ==============================================================================

    ModParentComponent.cpp
    Created: 25 Sep 2020 11:26:11am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ModParentComponent.h"

//==============================================================================

ModParentComponent::~ModParentComponent()
{
}

void ModParentComponent::paint (juce::Graphics& g)
{
   
}

void ModParentComponent::resized()
{
    int n = getHeight() / 24;
    oscSet.setBounds(0, 0, getWidth(),18 * n);
    lfo0.setBounds(0, 18 * n, 4 * n, 6 * n);
}

juce::DragAndDropTarget::SourceDetails ModParentComponent::getActiveSourceDetails(ModDestination* dest)
{
    auto activeDesc = getCurrentDragDescription();
    juce::Point<int> relativePoint = dest->getMouseXYRelative();
    juce::Component* activeComp;
    if(activeDesc == "lfo0Comp")
    {
        activeComp = &lfo0;
    }
    else
    {
        activeComp = nullptr;
    }
    auto details = juce::DragAndDropTarget::SourceDetails(activeDesc, activeComp, relativePoint);
    return details;
}

//this will call some function in the processor to assign the new slider depth values to each voice
void ModParentComponent::sliderValueChanged(juce::Slider* slider)
{
    DepthSlider* dSlider = dynamic_cast<DepthSlider*>(slider);
    int changedIndex = dSlider->oscIndex;
    juce::String newDestId = dSlider->destId;
    juce::String newSourceId = dSlider ->sourceId;
    audioProcessor.setModDepth(newSourceId, newDestId, changedIndex, dSlider->getValue());
}
