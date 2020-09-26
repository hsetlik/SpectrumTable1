/*
  ==============================================================================

    SpectrumOscillator.h
    Created: 22 Sep 2020 12:03:30pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include "ModProcessor.h"
#include <JuceHeader.h>

class HarmonicData
{
public:
    HarmonicData(int n) : index(n)
    {
        
    }
    ~HarmonicData(){}
    double getFrequencyFactor1(float p1)
    {
        return (double)(p1 * index) + 1.0f;
    }
    double getAmplitudeFactor1(float p0)
    {
        return (double)1.0f / ((p0 * index) + 1.0f);
    }
    double getFrequencyFactor2(float p1, float p0)
    {
        return (double)((p0 * index) + p1);
    }
    double getAmplitudeFactor2(float p1, float p0)
    {
        return (double)1.0f / (((p0 * index) + p1) - (p1 - 1.0f));
    }
private:
    int index;
};

class HarmonicOscillator
{
public:
    //functions
    HarmonicOscillator(int maxOvertones);
    ~HarmonicOscillator() {}
    float getNextSample();
    void setFundamental(float newFundamental)
    {
        fundamental = newFundamental;
    }
    //data
    std::vector<HarmonicData> harmonics;
    std::vector<maxiOsc> oscillators;
    float currentP1;
    float currentP0;
    float currentHarmonicCount;
    int maxHarmonicCount;
    bool secondAlgOn = false;
    bool p1Snap = false;
    bool p0Snap = false;
    maxiEnv envelope1;
    maxiEnv envelope2;
    //stuff for modulation
    bool p0HasSources = false;
    bool p1HasSources = false;
private:
    float fundamental = 0.0f;
    
};
