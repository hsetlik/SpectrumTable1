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
SpectrumParameterSet::SpectrumParameterSet(int index, GraphValueSet* values, juce::DragAndDropContainer* container, SpectrumTable1AudioProcessor& proc) :
graph(values),
envSliders(index),
parentContainer(container),
oscIndex(index),
p0Dest(container, "p0Dest", index, proc),
p1Dest(container, "p1Dest", index, proc),
nDest(container, "nDest", index, proc)
{
    addAndMakeVisible(&envSliders);
    addAndMakeVisible(&nSlider);
    addAndMakeVisible(&p0Slider);
    addAndMakeVisible(&p1Slider);
    addAndMakeVisible(&algButton);
    addAndMakeVisible(&graph);
    algButton.setButtonText("Compund Mode");
    algButton.setClickingTogglesState(true);
    
    addAndMakeVisible(&nDest);
    addAndMakeVisible(&p0Dest);
    addAndMakeVisible(&p1Dest);
    
    addAndMakeVisible(&p1SnapButton);
    p1SnapButton.setButtonText("Snap");
    p1SnapButton.setClickingTogglesState(true);
    
    addAndMakeVisible(&p0SnapButton);
    p0SnapButton.setButtonText("Snap");
    p0SnapButton.setClickingTogglesState(true);

    nSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    p0Slider.setSliderStyle(juce::Slider::LinearHorizontal);
    p1Slider.setSliderStyle(juce::Slider::LinearHorizontal);
    
    nSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    p0Slider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    p1Slider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 20);
    
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
    juce::String p1Name = "Parameter 1";
    juce::String algId = "algParam" + iStr;
    juce::String algName = "Serial Amplitude Modulation";
    juce::String p1SnapId = "p1SnapParam" + iStr;
    juce::String p1SnapName = "Parameter 1 Snap";
    juce::String p0SnapId = "p0SnapParam" + iStr;
    juce::String p0SnapName = "Parameter 0 Snap";
    
    auto aId = "attackParam"+ iStr;
    auto aName = "Oscillator " + iStr + " Attack";
    auto dId = "decayParam"+ iStr;
    auto dName = "Oscillator " + iStr + " Decay";
    auto sId = "sustainParam"+ iStr;
    auto sName = "Oscillator " + iStr + " Sustain";
    auto rId = "releaseParam"+ iStr;
    auto rName = "Oscillator " + iStr + " Release";
    
    juce::String p0DepthId = "p1DepthParam" + iStr;
    juce::String p0DepthName = "Oscillator " + iStr + " Parameter 1 mod depth";
    juce::String p1DepthId = "p1DepthParam" + iStr;
    juce::String p1DepthName = "Oscillator " + iStr + " Parameter 1 mod depth";
    juce::String nDepthId = "nDepthParam" + iStr;
    juce::String nDepthName = "Oscillator " + iStr + " harmonic count mod depth";
    
    newGroup.addChild(std::make_unique<juce::AudioParameterFloat>(p0DepthId, p0DepthName, 0.0, 0.0, 1.0));
    newGroup.addChild(std::make_unique<juce::AudioParameterFloat>(p1DepthId, p1DepthName, 0.0, 0.0, 1.0));
    newGroup.addChild(std::make_unique<juce::AudioParameterFloat>(nDepthId, nDepthName, 0.0, 0.0, 1.0));
    
    newGroup.addChild(std::make_unique<juce::AudioParameterFloat>(nId, nName, 1.0, 40.0, 6.0));
    newGroup.addChild(std::make_unique<juce::AudioParameterFloat>(p0Id, p0Name, 0.0, 15.0, 1.0));
    newGroup.addChild(std::make_unique<juce::AudioParameterFloat>(p1Id, p1Name, 1.0, 15.0, 1.0));
    newGroup.addChild(std::make_unique<juce::AudioParameterBool>(algId, algName, false));
    newGroup.addChild(std::make_unique<juce::AudioParameterBool>(p1SnapId, p1SnapName, false));
    newGroup.addChild(std::make_unique<juce::AudioParameterBool>(p0SnapId, p0SnapName, false));
    
    newGroup.addChild(std::make_unique<juce::AudioParameterFloat>(aId, aName, 1.0, 15000.0, 25.0));
    newGroup.addChild(std::make_unique<juce::AudioParameterFloat>(dId, dName, 1.0, 15000.0, 25.0));
    newGroup.addChild(std::make_unique<juce::AudioParameterFloat>(sId, sName, 0.0, 1.0, 6.0));
    newGroup.addChild(std::make_unique<juce::AudioParameterFloat>(rId, rName, 1.0, 15000.0, 25.0));
    
    return newGroup;
}

void SpectrumParameterSet::attachToTree(juce::AudioProcessorValueTreeState* pTree)
{
    juce::String iStr = juce::String(oscIndex);
    nAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree,
                                                                           "nParam" + iStr,
                                                                                  nSlider));
    p0Attach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree,
                                                                            "p0Param" + iStr,
                                                                                  p0Slider));
    p1Attach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree,
                                                                            "p1Param" + iStr,
                                                                                  p1Slider));
    algAttach.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(*pTree,
                                                                             "algParam" + iStr,
                                                                                  algButton));
    p1SnapAttach.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(*pTree,
                                                                             "p1SnapParam" + iStr,
                                                                                  p1SnapButton));
    p0SnapAttach.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(*pTree,
                                                                             "p0SnapParam" + iStr,
                                                                                  p0SnapButton));
    aAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree,
                                                                           "attackParam" + iStr,
                                                                                  envSliders.aSlider));
    dAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree,
                                                                           "decayParam" + iStr,
                                                                                  envSliders.dSlider));
    sAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree,
                                                                           "sustainParam" + iStr,
                                                                                  envSliders.sSlider));
    rAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree,
                                                                           "releaseParam" + iStr,
                                                                                  envSliders.rSlider));
    p0DAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "p0DepthParam" + iStr, p0Dest.depthSlider));
    
    p1DAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "p1DepthParam" + iStr, p1Dest.depthSlider));
    
    nDAttach.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(*pTree, "nDepthParam" + iStr, nDest.depthSlider));
    
    
}
void SpectrumParameterSet::paint (juce::Graphics& g)
{
    

}

void SpectrumParameterSet::resized()
{
    int l = getWidth() / 24;
    nSlider.setBounds(3 * l, l, 8 * l, l);
    nDest.setBounds(l / 2, l, 1.5 * l, 1.5 * l);
    p0Slider.setBounds(3 * l, 3 * l, 8 * l, l);
    p0Dest.setBounds(l / 2, 3 * l, 1.5 * l, 1.5 * l);
    p1Slider.setBounds(3 * l, 5 * l, 8 * l, l);
    p1Dest.setBounds(l / 2, 5 * l, 1.5 * l, 1.5 * l);
    p1SnapButton.setBounds(11 * l, 5 * l, 1.5 * l, l);
    p0SnapButton.setBounds(11 * l, 3 * l, 1.5 * l, l);
    algButton.setBounds(l, 7 * l, 4 * l, l);
    graph.setBounds(l * 13, l, 10 * l, 10 * l);
    envSliders.setBounds(l, 8 * l, 12 * l, 6 * l);
}
