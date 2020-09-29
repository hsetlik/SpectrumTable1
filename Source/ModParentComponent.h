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
#include "MixerComponent.h"

//==============================================================================
/*
*/
class ModParentComponent  : public juce::Component, public juce::DragAndDropContainer, public juce::Slider::Listener
{
public:
    ModParentComponent(SpectrumTable1AudioProcessor& proc) : oscSet(proc, this, this), lfo0("lfo0Source", this, 0), audioProcessor(proc)
    {
        addAndMakeVisible(&oscSet);
        addAndMakeVisible(&lfo0);
        addAndMakeVisible(&mixer);
    }
    ~ModParentComponent() override;
    void paint (juce::Graphics&) override;
    void resized() override;
    void attachAllChildrenToTree(juce::AudioProcessorValueTreeState* state)
    {
        oscSet.attachAllToTree(state);
        lfo0.attachToTree(state);
        mixer.attachToTree(state);
    }
    void sliderValueChanged(juce::Slider* slider) override;
    juce::DragAndDropTarget::SourceDetails getActiveSourceDetails(ModDestination* dest);
    OscillatorSet oscSet;
    LfoComponent lfo0;
    OscMixerComponent mixer;
    juce::String activeDesc;
    SpectrumTable1AudioProcessor& audioProcessor;
    
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModParentComponent)
};

