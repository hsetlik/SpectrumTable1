/*
  ==============================================================================

    SpectrumSynthVoice.h
    Created: 22 Sep 2020 10:29:40am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SpectrumOscillator.h"
#include "ModProcessor.h"

class SpectrumSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int /*midiNoteNumber*/) //just plays this sound for any midi note
    {
        return true;
    }
    bool appliesToChannel(int /*midiChannel*/) //plays the sound on both channels
    {
        return true;
    }
};

class SpectrumVoice : public juce::SynthesiserVoice
{
public:
    SpectrumVoice()
    {
        for(int i = 0; i < 3; ++i)
        {
            std::unique_ptr<HarmonicOscillator> newOsc(new HarmonicOscillator(40));
            allOscs.push_back(*newOsc);
            float* rP0 = &allOscs.back().currentP0;
            float* rP1 = &allOscs.back().currentP1;
            float* rN = &allOscs.back().currentHarmonicCount;
            std::unique_ptr<OscillatorModHandler>newHandler(new OscillatorModHandler(rP0, rP1, rN, i));
            oscHandlers.push_back(*newHandler);
        }
    }
    
    //MODULATION INPUT FUNCTIONS - each ModGenerator  parameter in the handler needs a function
    void setLfo0Rate(std::atomic<float>* value, int index)
    {
        OscillatorModHandler* thisHandler = &oscHandlers[index];
        thisHandler->lfoGen0.setRate(*value);
    }
    void setP0Depth(std::atomic<float>* value, int index)
    {
        OscillatorModHandler* thisHandler = &oscHandlers[index];
        thisHandler->p0ModDepth = *value;
    }
    void setP1Depth(std::atomic<float>* value, int index)
    {
        OscillatorModHandler* thisHandler = &oscHandlers[index];
        thisHandler->p1ModDepth = *value;
    }
    void setNDepth(std::atomic<float>* value, int index)
    {
        OscillatorModHandler* thisHandler = &oscHandlers[index];
        thisHandler->nModDepth = *value;
    }
    
    //PARAMETER INPUT FUNCTIONS
    void setVoiceP0(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = &allOscs[index];
        if(thisOsc->p0Snap)
            thisOsc->currentP0 = floor(*value);
        else
            thisOsc->currentP0 = *value;
    }
    void setVoiceP1(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = &allOscs[index];
        if(thisOsc->p1Snap)
            thisOsc->currentP1 = floor(*value);
       else
           thisOsc->currentP1 = *value;
    }
    void setVoiceP1Snap(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = &allOscs[index];
        thisOsc->p1Snap = (bool)(*value);
    }
    void setVoiceP0Snap(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = &allOscs[index];
        thisOsc->p0Snap = (bool)(*value);
    }
    void setNumHarmonics(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = &allOscs[index];
        thisOsc->currentHarmonicCount = floor(*value);
    }
    void setAlgChoice(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = &allOscs[index];
        thisOsc->secondAlgOn = (bool)(*value);
    }
    void setAttack(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = &allOscs[index];
        thisOsc->envelope1.setAttack(*value);
    }
    void setDecay(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = &allOscs[index];
        thisOsc->envelope1.setDecay(*value);
    }
    void setSustain(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = &allOscs[index];
        thisOsc->envelope1.setSustain(*value);
    }
    void setRelease(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = &allOscs[index];
        thisOsc->envelope1.setRelease(*value);
    }
    //END PARAMETER INPUTS================================
    bool canPlaySound(juce::SynthesiserSound* sound)
    {
        return dynamic_cast<SpectrumSound*>(sound) != nullptr;
    }
    void startNote (int midiNoteNumber,
                    float velocity,
                    juce::SynthesiserSound *sound,
                    int currentPitchWheelPosition)
    {
        auto newPitch = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        for(int i = 0; i < 3; ++i)
        {
            allOscs[i].setFundamental(newPitch);
            allOscs[i].envelope1.trigger = 1;
        }
    }
    void stopNote (float velocity, bool allowTailOff)
    {
        for(int i = 0; i < 3; ++i)
        {
            allOscs[i].envelope1.trigger = 0;
        }
        allowTailOff = true;
        if(velocity == 0)
            clearCurrentNote();
    }
    //===========================================
    void pitchWheelMoved(int newPitchWheelVal)
    {
        
    }
    //=============================================
    void controllerMoved(int controllerNumber, int controllerValue)
    {
        
    }
    //===============================================
    void aftertouchChanged (int newAftertouchValue)
    {

    }
    //==============================================
    void channelPressureChanged (int newChannelPressureValue)
    {
        
    }
    //===============================================
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
    {
        for(int i = 0; i < numSamples; ++i)
        {
            float sum = 0.0f;
            for(int g = 0; g < 3; ++g)
            {
                oscHandlers[g].applyAllMods();
                float newPreEnv = allOscs[g].getNextSample();
                sum += (allOscs[g].envelope1.adsr(newPreEnv, allOscs[g].envelope1.trigger));
            }
            newSample = sum / 3.0f;
            for(int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, newSample);
            }
            ++startSample;
        }
       
    }
    //==============================================
    void setCurrentPlaybackSampleRate (double newRate)
    {
        
    }
    float newSample = 0.0f;
    std::vector<HarmonicOscillator> allOscs;
    std::vector<OscillatorModHandler> oscHandlers;
};
