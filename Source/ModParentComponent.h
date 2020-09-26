/*
  ==============================================================================

    ModParentComponent.h
    Created: 25 Sep 2020 11:26:11am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "OscillatorGroup.h"
#include "ModDestination.h"


//==============================================================================
/*
*/
class ModParentComponent  : public juce::Component, public juce::DragAndDropContainer
{
public:
    ModParentComponent(SpectrumTable1AudioProcessor& proc) : oscSet(proc, this), lfo0("lfo0", this, 0)
    {
        addAndMakeVisible(&oscSet);
        addAndMakeVisible(&lfo0);
    }
    ~ModParentComponent() override;
    void paint (juce::Graphics&) override;
    void resized() override;
    void attachAllChildrenToTree(juce::AudioProcessorValueTreeState* state)
    {
        oscSet.attachAllToTree(state);
        lfo0.attachToTree(state);
    }
    
    std::vector<ModDestination> allDestinations;
    juce::DragAndDropTarget::SourceDetails getActiveSourceDetails(ModDestination* dest);
    OscillatorSet oscSet;
    LfoComponent lfo0;
    juce::String activeDesc;
    
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModParentComponent)
};

