/*
  ==============================================================================

    SpectrumOscillator.cpp
    Created: 22 Sep 2020 12:03:30pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "SpectrumOscillator.h"
HarmonicOscillator::HarmonicOscillator(int maxOvertones) : maxHarmonicCount(maxOvertones)
{
    envelope.setAttack(20.0);
    envelope.setRelease(85.0);
    envelope.setSustain(0.6);
    envelope.setRelease(150);
    for(int i = 0; i < maxHarmonicCount; ++i)
    {
        std::unique_ptr<HarmonicData> newHarmonic(new HarmonicData(i));
        std::unique_ptr<maxiOsc> newOsc(new maxiOsc);
        harmonics.push_back(*newHarmonic);
        oscillators.push_back(*newOsc);
    }
}

float HarmonicOscillator::getNextSample()
{
    float returnSample = 0.0f;
    for(int i = 0; i < currentHarmonicCount; ++i)
    {
        double newFreq;
        
        double newAmp;
        if(secondAlgOn)
        {
            newFreq = fundamental * harmonics[i].getFrequencyFactor2(currentP1, currentP0);
            newAmp = harmonics[i].getAmplitudeFactor2(currentP1, currentP0);
        }
        else
        {
            newFreq = fundamental * harmonics[i].getFrequencyFactor1(currentP1);
            newAmp = harmonics[i].getAmplitudeFactor1(currentP0);
        }
        auto newPreEnv = oscillators[i].sinewave(newFreq);
        returnSample += (newPreEnv * newAmp);
    }
    return returnSample;
}
