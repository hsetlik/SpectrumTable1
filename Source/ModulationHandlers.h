/*
  ==============================================================================

    ModulationHandlers.h
    Created: 25 Sep 2020 9:41:03am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "OscillatorGroup.h"

class FloatModSource
{
    FloatModSource();
    virtual ~FloatModSource() {}
    virtual void setValue(float newValue)
    {
        currentValue = newValue;
    }
    float getValue()
    {
        return currentValue;
    }
private:
    float currentValue = 0.0f;
};

class OscillatorModDest
{
public:
    OscillatorModDest(float* destParameter);
    ~OscillatorModDest() {}
    void addSource(FloatModSource* src)
    {
        source = src;
        isConnected = true;
    }
    void applyModulation()
    {
        
    }
private:
    bool isConnected;
    FloatModSource* source;
    float* destination;
    
};
