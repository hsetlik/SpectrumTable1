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
    SpectrumVoice() : osc1(40), osc2(40), osc3(40)
    {
        printf("voice created\n");
        for(int i = 0; i < 3; ++i)
        {
            std::unique_ptr<HarmonicOscillator> newOsc(new HarmonicOscillator(40));
            allOscs.push_back(*newOsc);
            newOsc->envelope1.setAttack(25.0f);
            newOsc->envelope1.setDecay(55.0f);
            newOsc->envelope1.setSustain(0.6f);
            newOsc->envelope1.setRelease(100.0f);
        }
    }
    //PARAMETER INPUT FUNCTIONS
    void setVoiceP0(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = &allOscs[index];
        if(thisOsc->secondAlgOn)
            thisOsc->currentP0 = floor(*value);
        else
            thisOsc->currentP0 = *value;
    }
    void setVoiceP1(std::atomic<float>* value, int index)
    {
        HarmonicOscillator* thisOsc = &allOscs[index];
        if(thisOsc->secondAlgOn)
            thisOsc->currentP1 = floor(*value);
        else
            thisOsc->currentP1 = *value;
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
            allOscs[i].fundamental = newPitch;
            allOscs[i].envelope1.setAttack(25.0f);
            allOscs[i].envelope1.setDecay(85.0f);
            allOscs[i].envelope1.setSustain(0.6f);
            allOscs[i].envelope1.setRelease(100.0f);
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
            for(int i = 0; i < 3; ++i)
            {
                float newPreEnv = allOscs[i].getNextSample();
                sum += allOscs[i].envelope1.adsr(newPreEnv, allOscs[i].envelope1.trigger);
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
    HarmonicOscillator osc1;
    HarmonicOscillator osc2;
    HarmonicOscillator osc3;
};
