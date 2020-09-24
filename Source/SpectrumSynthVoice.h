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
    SpectrumVoice() : osc(40)
    {
        printf("voice created\n");
    }
    //PARAMETER INPUT FUNCTIONS
    void setVoiceP0(std::atomic<float>* value)
    {
        if(osc.secondAlgOn)
            osc.currentP0 = floor(*value);
        else
            osc.currentP0 = *value;
    }
    void setVoiceP1(std::atomic<float>* value)
    {
        if(osc.secondAlgOn)
            osc.currentP1 = floor(*value);
        else
            osc.currentP1 = *value;
    }
    void setNumHarmonics(std::atomic<float>* value)
    {
        osc.currentHarmonicCount = floor(*value);
    }
    void setAlgChoice(std::atomic<float>* value)
    {
        osc.secondAlgOn = (bool)(*value);
    }
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
        osc.fundamental = newPitch;
        osc.envelope.trigger = 1;
       
    }
    void stopNote (float velocity, bool allowTailOff)
    {
        osc.envelope.trigger = 0;
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
        osc.envelope.setAttack(25.0f);
        osc.envelope.setDecay(85.0f);
        osc.envelope.setSustain(0.6f);
        osc.envelope.setRelease(250.0f);
        for(int i = 0; i < numSamples; ++i)
        {
            float newPreEnv = osc.getNextSample();
            float newSample = osc.envelope.adsr(newPreEnv, osc.envelope.trigger);
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
    HarmonicOscillator osc;
};
