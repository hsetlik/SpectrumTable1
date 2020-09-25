/*
  ==============================================================================

    SpectrumParameterSet.h
    Created: 22 Sep 2020 12:06:10pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MaxiOscGraph.h"
#include "EnvelopeSliderSet.h"
//==============================================================================
/*
*/
class SpectrumParameterSet  : public juce::Component
{
public:
    SpectrumParameterSet(int oscillatorIndex, GraphValueSet* values);
    ~SpectrumParameterSet() override;
    void attachToTree(juce::AudioProcessorValueTreeState* pTree);
    void paint (juce::Graphics&) override;
    void resized() override;
    juce::AudioProcessorParameterGroup createParamGroup();
    
    juce::AudioProcessor* audioProcessor;
    juce::Slider nSlider;
    juce::Slider p0Slider;
    juce::Slider p1Slider;
    juce::TextButton algButton;
    
    MaxiOscGraph graph;
    EnvelopeSliderSet envSliders;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> nAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> p0Attach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> p1Attach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> algAttach;
    
    //stuff for the envelope
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> aAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rAttach;
    
    int oscIndex;
private:
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectrumParameterSet)
};
