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
    ModParentComponent(SpectrumTable1AudioProcessor& proc) : oscSet(proc)
    {
        addAndMakeVisible(&oscSet);
        
    }
    ~ModParentComponent() override;
    void paint (juce::Graphics&) override;
    void resized() override;
    OscillatorSet oscSet;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModParentComponent)
};

