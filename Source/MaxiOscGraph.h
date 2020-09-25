/*
  ==============================================================================

    MaxiOscGraph.h
    Created: 24 Sep 2020 9:23:02am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "maximilian.h"
#include "SpectrumOscillator.h"
#include "OscilloscopeComponent.h"
//==============================================================================
/*
*/
const int frameRate = 24;

class GraphValueSet
{
public:
    //functions
    GraphValueSet(int maxOvertones);
    ~GraphValueSet() {}
    void setNumHarmonics(std::atomic<float>* value)
    {
        currentNumHarmonics = *value;
    }
    void setP0(std::atomic<float>* value)
    {
        currentP0 = *value;
    }
    void setP1(std::atomic<float>* value)
    {
        if(secondAlgOn)
            currentP1 = floor(*value);
        else
            currentP1 = *value;
    }
    void setAlgSelection(std::atomic<float>* value)
    {
        secondAlgOn = (bool)(*value);
    }
    void setPitch(float pitch)
    {
        currentFundamental = pitch;
    }
    void setMasterVol(float amp)
    {
        masterAmplitude = amp;
    }
    void setDisplayPoints();
    //data
    std::vector<HarmonicData> harmonicData;
    std::vector<float> fAmplitudes;
    std::vector<float> pointsToDisplay;
    std::vector<float> angleDeltas;
    std::vector<float> currentAngles;
    
private:
    float masterAmplitude = 1.0f;
    float currentFundamental = 440.0f;
    int currentNumHarmonics = 0;
    bool secondAlgOn = false;
    float currentP0 = 1;
    float currentP1 = 1;
};



class MaxiOscGraph  : public juce::Component, public juce::Timer
{
public:
    MaxiOscGraph(GraphValueSet* valueSet);
    ~MaxiOscGraph() override;
    void timerCallback() override
    {
        repaint();
    }
    void paint (juce::Graphics&) override;
private:
    std::vector<float> waveDataPoints;
    float amplitude = 140.0f;
    GraphValueSet* values;
    juce::Colour backgroundColor = juce::Colours::darkgrey;
    juce::Colour traceColor = juce::Colours::orange;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MaxiOscGraph)
};
