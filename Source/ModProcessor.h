/*
  ==============================================================================

    ModProcessor.h
    Created: 26 Sep 2020 11:54:30am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ModGenerator.h"

/* TODO
 -the synthVoice should create one of these
 for each oscillator
 -the synthVoice needs to have functions which take
 tree parameter and index to assign settings on the ModGenerator objects
 */
class OscillatorModHandler
{
public:
    //functions
    OscillatorModHandler(float* P0, float* P1, float* N, int oscIndex);
    ~OscillatorModHandler() {}
    //data
    bool p1HasSource = false;
    bool p0HasSource = false;
    bool nHasSource = false;
    int index;
    float* p1Target;
    float* p0Target;
    float* nTarget;
    //these need to somehow get called by the appropriate itemDropped functions in the ModDestination component
    void addP0Source(juce::String sourceId)
    {
        p0SourceIds.push_back(sourceId);
        if(p0HasSource == false)
            p0HasSource = true;
    }
    void addP1Source(juce::String sourceId)
    {
        p1SourceIds.push_back(sourceId);
        if(p1HasSource == false)
            p1HasSource = true;
    }
    void addNSource(juce::String sourceId)
    {
        nSourceIds.push_back(sourceId);
        if(nHasSource == false)
            nHasSource = true;
    }
    void applyP0Mod();
    float p0ModDepth;
    void applyP1Mod();
    float p1ModDepth;
    void applyNMod();
    float nModDepth;
    void applyAllMods();
    //these store the idStrings for each of the mod sources arrached to each parameter of the osc
    std::vector<juce::String> p1SourceIds;
    std::vector<juce::String> p0SourceIds;
    std::vector<juce::String> nSourceIds;
    LfoGenerator lfoGen0;
};
