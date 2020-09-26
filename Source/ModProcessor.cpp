/*
  ==============================================================================

    ModProcessor.cpp
    Created: 26 Sep 2020 11:54:30am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "ModProcessor.h"

OscillatorModHandler::OscillatorModHandler(float* P0, float* P1, float* N, int oscIndex) :
index(oscIndex), p1Target(P1), p0Target(P0), nTarget(N), lfo0("lfo0")
{
    p1SourceIds.clear();
    p0SourceIds.clear();
    nSourceIds.clear();
}

void OscillatorModHandler::applyP0Mod()
{
    if(p0HasSource)
    {
        for(int i = 0; i < p0SourceIds.size(); ++i)
        {
            if(p0SourceIds[i] == "lfo0")
                *p0Target += lfo0.getNextSampleValue();
        }
    }
}

void OscillatorModHandler::applyP1Mod()
{
    if(p1HasSource)
    {
        for(int i = 0; i < p1SourceIds.size(); ++i)
        {
            if(p1SourceIds[i] == "lfo0")
                *p1Target += lfo0.getNextSampleValue();
        }
    }
}

void OscillatorModHandler::applyNMod()
{
    if(nHasSource)
    {
        for(int i = 0; i < nSourceIds.size(); ++i)
        {
            if(nSourceIds[i] == "lfo0")
                *nTarget += lfo0.getNextSampleValue();
        }
    }
}
