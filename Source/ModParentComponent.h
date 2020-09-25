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
#include "ModSourceComponent.h"
//==============================================================================
/*
*/
class ModParentComponent  : public juce::Component, public juce::DragAndDropContainer
{
public:
    ModParentComponent(SpectrumTable1AudioProcessor& proc) : oscSet(proc), lfo0("lfo", this, 0)
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
    OscillatorSet oscSet;
    LfoComponent lfo0;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModParentComponent)
};

