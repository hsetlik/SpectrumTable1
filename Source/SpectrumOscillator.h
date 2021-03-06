/*
  ==============================================================================

    SpectrumOscillator.h
    Created: 22 Sep 2020 12:03:30pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include "maximilian.h"
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
    //data
    std::vector<HarmonicData> harmonics;
    std::vector<maxiOsc> oscillators;
    void setFundamental(float newFundamental)
    {
        fundamental = newFundamental;
    }
    void applyAllModulations()
    {
        currentP1 += p1Mod;
        currentP0 += p0Mod;
        currentHarmonicCount += floor(nMod);
    }
    float currentP1;
    float p1Mod = 0.0f;
    float currentP0;
    float p0Mod = 0.0f;
    int currentHarmonicCount;
    float nMod = 0.0f;
    int maxHarmonicCount;
    bool secondAlgOn = false;
    bool p1Snap = false;
    bool p0Snap = false;
    maxiEnv envelope1;
    maxiEnv envelope2;
private:
    float fundamental = 0.0f;
};
