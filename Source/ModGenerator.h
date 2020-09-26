/*
  ==============================================================================

    ModGenerator.h
    Created: 26 Sep 2020 11:58:26am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "maximilian.h"
/*
 abstract base class for anything that generates a modulation signal as a floating point number between 0 and 1
 override the getNextSampleValue function to do calculations from the source
 */
class ModGenerator
{
public:
    ModGenerator()
    {
    }
    virtual ~ModGenerator() {}
    virtual float getNextSampleValue()
    {
        return 0.0f;
    }
    
};

class LfoGenerator : public ModGenerator
{
public:
    LfoGenerator(juce::String idStr) : typeId(idStr)
    {
        lfoRate = 1.0f;
    }
    ~LfoGenerator(){}
    void setRate(float newRate)
    {
        lfoRate = newRate;
    }
    void setDepth(float newDepth)
    {
        depth = newDepth;
    }
    float getNextSampleValue() override
    {
        float sample = ((osc.sinebuf(lfoRate) + 1.0f) / 2.0f); //changes range from -1, 1 to 0, 1
        return (sample * depth);
    }
    juce::String typeId;
private:
    float depth = 1.0f;
    float lfoRate = 0;
    maxiOsc osc;
};