/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SpectrumParameterSet.h"
#include "OscilloscopeComponent.h"
#include "OscillatorGroup.h"


//==============================================================================
/**
*/
class SpectrumTable1AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SpectrumTable1AudioProcessorEditor (SpectrumTable1AudioProcessor&);
    ~SpectrumTable1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    SpectrumTable1AudioProcessor& audioProcessor;
    //MaxiOscGraph graph;
    OscillatorSet allOscs;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectrumTable1AudioProcessorEditor)
};
