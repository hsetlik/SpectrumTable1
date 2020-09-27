/*
  ==============================================================================

    ModProcessor.cpp
    Created: 26 Sep 2020 11:54:30am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "ModProcessor.h"

OscillatorModHandler::OscillatorModHandler(float* P0, float* P1, float* N, int oscIndex) :
index(oscIndex), p1Target(P1), p0Target(P0), nTarget(N), lfoGen0("lfoGen0")
{
    p1SourceIds.clear();
    p0SourceIds.clear();
    nSourceIds.clear();
    p0ModDepth = 1.0f;
    p1ModDepth = 1.0f;
    nModDepth = 1.0f;
}

void OscillatorModHandler::applyP0Mod()
{
    if(p0HasSource)
    {
        for(int i = 0; i < p0SourceIds.size(); ++i)
        {
            if(p0SourceIds[i] == "lfo0Source")
                *p0Target += lfoGen0.getNextSampleValue();
        }
    }
}

void OscillatorModHandler::applyP1Mod()
{
    if(p1HasSource)
    {
        for(int i = 0; i < p1SourceIds.size(); ++i)
        {
            if(p1SourceIds[i] == "lfo0Source")
                *p1Target += lfoGen0.getNextSampleValue();
        }
    }
}

void OscillatorModHandler::applyNMod()
{
    if(nHasSource)
    {
        for(int i = 0; i < nSourceIds.size(); ++i)
        {
            if(nSourceIds[i] == "lfo0Source")
                *nTarget += lfoGen0.getNextSampleValue();
        }
    }
}

void OscillatorModHandler::applyAllMods()
{
    applyP0Mod();
    applyP1Mod();
    applyNMod();
}
