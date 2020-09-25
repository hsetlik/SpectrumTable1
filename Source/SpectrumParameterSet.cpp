/*
  ==============================================================================

    SpectrumParameterSet.cpp
    Created: 22 Sep 2020 12:06:10pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SpectrumParameterSet.h"

//==============================================================================
SpectrumParameterSet::SpectrumParameterSet(int index, GraphValueSet* values) :  graph(values), oscIndex(index)
{
    addAndMakeVisible(&nSlider);
    addAndMakeVisible(&p0Slider);
    addAndMakeVisible(&p1Slider);
    addAndMakeVisible(&algButton);
    addAndMakeVisible(&graph);
    algButton.setButtonText("Algorithm");
    algButton.setClickingTogglesState(true);

    nSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    p0Slider.setSliderStyle(juce::Slider::LinearHorizontal);
    p1Slider.setSliderStyle(juce::Slider::LinearHorizontal);
    
    nSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 50, 20);
    p0Slider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 50, 20);
    p1Slider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 50, 20);
    
    nSlider.setRange(1.0f, 40.0f);
    p0Slider.setRange(0.0f, 15.0f);
    p1Slider.setRange(1.0f, 15.0f);
    
    nSlider.setValue(1.0f);
    p0Slider.setValue(1.0f);
    p1Slider.setValue(1.0f);
}

SpectrumParameterSet::~SpectrumParameterSet()
{
}

juce::AudioProcessorParameterGroup SpectrumParameterSet::createParamGroup()
{
    juce::String iStr = juce::String(oscIndex);
    juce::String groupId = "osc" + iStr;
    juce::String groupName = "Oscillator " + iStr;
    juce::AudioProcessorParameterGroup newGroup(groupId, groupName, "|");
    
    juce::String p0Id = "p0Param" + iStr;
    juce::String p0Name = "Parameter 0";
    juce::String nId = "nParam" + iStr;
    juce::String nName = "number of harmonics";
    juce::String p1Id = "p1Param" + iStr;
    juce::String p1Name = "Parameter 2";
    juce::String algId = "algParam" + iStr;
    juce::String algName = "Serial Amplitude Modulation";
    
    newGroup.addChild(std::make_unique<juce::AudioParameterFloat>(nId, nName, 1.0, 40.0, 6.0));
    newGroup.addChild(std::make_unique<juce::AudioParameterFloat>(p0Id, p0Name, 0.0, 15.0, 1.0));
    newGroup.addChild(std::make_unique<juce::AudioParameterFloat>(p1Id, p1Name, 1.0, 15.0, 1.0));
    newGroup.addChild(std::make_unique<juce::AudioParameterBool>(algId, algName, false));
    
    return newGroup;
}

void SpectrumParameterSet::attachToTree(juce::AudioProcessorValueTreeState* pTree)
{
    juce::String iStr = juce::String(oscIndex);
    nAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "nParam" + iStr,
                                                                                  nSlider));
    p0Attach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "p0Param" + iStr,
                                                                                  p0Slider));
    p1Attach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "p1Param" + iStr,
                                                                                  p1Slider));
    algAttach.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(*pTree, "algParam" + iStr,
                                                                                  algButton));
}
void SpectrumParameterSet::paint (juce::Graphics& g)
{
    

}

void SpectrumParameterSet::resized()
{
    int l = getWidth() / 24;
    nSlider.setBounds(l, l, 10 * l, l);
    p0Slider.setBounds(l, 3 * l, 10 * l, l);
    p1Slider.setBounds(l, 5 * l, 10 * l, l);
    algButton.setBounds(l, 7 * l, 4 * l, l);
    graph.setBounds(l * 11, l, 10 * l, 10 * l);
    

}
