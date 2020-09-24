/*
  ==============================================================================

    OscillatorGroup.h
    Created: 24 Sep 2020 12:07:40pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SpectrumParameterSet.h"
#include "MaxiOscGraph.h"






const int totalOscillators = 3;
//==============================================================================
/*
*/
class OscillatorSet  : public juce::TabbedComponent
{
public:
    OscillatorSet() : juce::TabbedComponent(juce::TabbedButtonBar::TabsAtTop), pSet1(0), pSet2(1), pSet3(2)
    {
        setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
        setTabBarDepth(25);
        addTab("Osc 1", tabBkgnd, &pSet1, false);
        addTab("Osc 2", tabBkgnd, &pSet2, false);
        addTab("Osc 3", tabBkgnd, &pSet3, false);
        
        addAndMakeVisible(&pSet1);
        addAndMakeVisible(&pSet2);
        addAndMakeVisible(&pSet3);
        
        setCurrentTabIndex(0);
    }
    ~OscillatorSet() {}
    juce::AudioProcessorParameterGroup createGroup();
    void attachAllToTree(juce::AudioProcessorValueTreeState* target)
    {
        pSet1.attachToTree(target);
        pSet2.attachToTree(target);
        pSet3.attachToTree(target);
    }
    SpectrumParameterSet pSet1;
    SpectrumParameterSet pSet2;
    SpectrumParameterSet pSet3;
private:
    juce::Colour tabBkgnd = juce::Colours::darkslategrey;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorSet)
};
