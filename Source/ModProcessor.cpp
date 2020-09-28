/*
  ==============================================================================

    ModProcessor.cpp
    Created: 26 Sep 2020 11:54:30am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "ModProcessor.h"


void ModDestProcessor::addSource(juce::String sourceId)
{
    //IMPORTANT every mod source named in the AllGenerators class needs to be checked in an else if statement here
    if(sourceId == "lfo0Source")
        sources.add(new ModSourceProcessor(sourceId, allGens->pLfo0));
}

float ModDestProcessor::getParameterDelta()
{
    float sum = 0.0f;
    if(sources.size() != 0)
    {
        for(int i = 0; i < sources.size(); ++i)
        {
            sum += sources[i]->getNextSampleValue();
        }
        return (float)(sum / sources.size());
    }
    else
        return 0.0f;
}
