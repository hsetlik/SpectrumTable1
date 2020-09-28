/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

juce::AudioProcessorValueTreeState::ParameterLayout createLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    for(int i = 0; i < 3; ++i)
    {
    juce::String iStr = juce::String(i);
    juce::String p0Id = "p0Param" + iStr;
    juce::String p0Name = "Parameter 0";
    juce::String nId = "nParam" + iStr;
    juce::String nName = "number of harmonics";
    juce::String p1Id = "p1Param" + iStr;
    juce::String p1Name = "Parameter 2";
    juce::String algId = "algParam" + iStr;
    juce::String algName = "Serial Amplitude Modulation";
    juce::String p1SnapId = "p1SnapParam" + iStr;
    juce::String p1SnapName = "Parameter 1 Snap";
    juce::String p0SnapId = "p0SnapParam" + iStr;
    juce::String p0SnapName = "Parameter 0 Snap";
        
    juce::String aId = "attackParam" + iStr;
    juce::String aName = "Oscillator " + iStr + " Attack";
    juce::String dId = "decayParam" + iStr;
    juce::String dName = "Oscillator " + iStr + " Decay";
    juce::String sId = "sustainParam" + iStr;
    juce::String sName = "Oscillator " + iStr + " Sustain";
    juce::String rId = "releaseParam" + iStr;
    juce::String rName = "Oscillator " + iStr + " Release";
    
    layout.add(std::make_unique<juce::AudioParameterFloat>(aId, aName, 1.0, 15000.0, 25.0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(dId, dName, 1.0, 15000.0, 65.0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(sId, sName, 0.0, 1.0, 0.6));
    layout.add(std::make_unique<juce::AudioParameterFloat>(rId, rName, 1.0, 15000.0, 100.0));
    
    layout.add(std::make_unique<juce::AudioParameterFloat>(nId, nName, 1.0, 40.0, 6.0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(p0Id, p0Name, 0.0, 15.0, 1.0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(p1Id, p1Name, 1.0, 15.0, 1.0));
    layout.add(std::make_unique<juce::AudioParameterBool>(algId, algName, false));
    layout.add(std::make_unique<juce::AudioParameterBool>(p1SnapId, p1SnapName, false));
    layout.add(std::make_unique<juce::AudioParameterBool>(p0SnapId, p0SnapName, false));
    }
    auto lfoId = "lfoParam0";
    auto lfoName = "LFO 1 Frequency";
    layout.add(std::make_unique<juce::AudioParameterFloat>(lfoId, lfoName, 0.01f, 20.0f, 1.0f));
    return layout;
}



//==============================================================================
SpectrumTable1AudioProcessor::SpectrumTable1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), tree(*this, nullptr, "ALLPARAMETERS", createLayout())
#endif
{
    for(int i = 0; i < 6; ++i)
    {
        synth.addVoice(new SpectrumVoice());
    }
    synth.clearSounds();
    synth.addSound(new SpectrumSound());
    //filling up the source with empty buffers so we have a line at the beginning
    for(int i = 0; i < 3; ++i)
    {
        std::unique_ptr<GraphValueSet> newValSet(new GraphValueSet(40));
        allGraphValues.push_back(*newValSet);
    }
}

SpectrumTable1AudioProcessor::~SpectrumTable1AudioProcessor()
{
}

//==============================================================================
const juce::String SpectrumTable1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SpectrumTable1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SpectrumTable1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SpectrumTable1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SpectrumTable1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SpectrumTable1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SpectrumTable1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void SpectrumTable1AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SpectrumTable1AudioProcessor::getProgramName (int index)
{
    return {};
}

void SpectrumTable1AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SpectrumTable1AudioProcessor::prepareToPlay (double rate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused(samplesPerBlock);
    synth.setCurrentPlaybackSampleRate(rate);
}

void SpectrumTable1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SpectrumTable1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SpectrumTable1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    for(int i = 0; i < synth.getNumVoices(); ++i)
    {
        if((thisVoice =  dynamic_cast<SpectrumVoice*>(synth.getVoice(i))))
        {
            for(int n = 0; n < 3; ++n)
            {
                juce::String nStr = juce::String(n);
                juce::String aName = "attackParam" + nStr;
                juce::String dName = "decayParam" + nStr;
                juce::String sName = "sustainParam" + nStr;
                juce::String rName = "releaseParam" + nStr;
                juce::String nName = "nParam" + nStr;
                juce::String p0Name = "p0Param" + nStr;
                juce::String p1Name = "p1Param" + nStr;
                juce::String algName = "algParam" + nStr;
                juce::String p1SnapName = "p1SnapParam" + nStr;
                juce::String lfoRateName = "lfoParam0";
               
                thisVoice->setVoiceP1Snap(tree.getRawParameterValue(p1SnapName), n);
                thisVoice->setAttack(tree.getRawParameterValue(aName), n);
                thisVoice->setDecay(tree.getRawParameterValue(dName), n);
                thisVoice->setSustain(tree.getRawParameterValue(sName), n);
                thisVoice->setRelease(tree.getRawParameterValue(rName), n);
                
                thisVoice->setNumHarmonics(tree.getRawParameterValue(nName), n);
                thisVoice->setVoiceP0(tree.getRawParameterValue(p0Name), n);
                thisVoice->setVoiceP1(tree.getRawParameterValue(p1Name), n);
                thisVoice->setAlgChoice(tree.getRawParameterValue(algName), n);
                
            }
        }
    }
    buffer.clear();
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    float masterLevel = buffer.getRMSLevel(0, 0, buffer.getNumSamples());
    for(int i = 0; i < 3; ++i)
    {
        juce::String iStr = juce::String(i);
        auto nPar = "nParam" + iStr;
        auto p0Par = "p0Param" + iStr;
        auto p1Par = "p1Param" + iStr;
        auto algPar = "algParam" + iStr;
        
        allGraphValues[i].setNumHarmonics(tree.getRawParameterValue(nPar));
        allGraphValues[i].setP0(tree.getRawParameterValue(p0Par));
        allGraphValues[i].setP1(tree.getRawParameterValue(p1Par));
        allGraphValues[i].setAlgSelection(tree.getRawParameterValue(algPar));
        allGraphValues[i].setMasterVol(masterLevel);
        allGraphValues[i].setDisplayPoints();
    }
}

//==============================================================================
bool SpectrumTable1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SpectrumTable1AudioProcessor::createEditor()
{
    return new SpectrumTable1AudioProcessorEditor (*this);
}

//==============================================================================
void SpectrumTable1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SpectrumTable1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void SpectrumTable1AudioProcessor::addVoiceModulation(juce::String sourceId, juce::String destId, int index)
{
    //loop through all voices
    for(int voice = 0; voice < synth.getNumVoices(); ++voice)
    {
    SpectrumVoice* currentVoice = dynamic_cast<SpectrumVoice*>(synth.getVoice(voice));
    //grab the correct oscillator for the index
    HarmonicOscillator* currentOsc = currentVoice->allOscs[index];
    //grab the correct ModDestProcessor for the ID
    ModDestProcessor* currentDest;
        if(destId == "p0Dest")
            currentDest = &currentOsc->p0ModProc;
        else if(destId == "p1Dest")
            currentDest = &currentOsc->p1ModProc;
        else if(destId == "nDest")
            currentDest = &currentOsc->nModProc;
        else
            currentDest = nullptr;
    //ModDestProcessor.addSource(sourceId)
        currentDest->addSource(sourceId);
    }
}

void SpectrumTable1AudioProcessor::setModDepth(juce::String sourceId, juce::String destId, int index, float value)
{
    //loop through all the modulations until one with matching sourceId, destId, and index is found
    for(int g = 0; g < synth.getNumVoices(); ++g)
    {
        SpectrumVoice* currentVoice = dynamic_cast<SpectrumVoice*>(synth.getVoice(g));
        for(int oscInd = 0; oscInd < 3; ++oscInd)
        {
            if(index == oscInd)
            {
               if(destId == "p0Dest")
               {
                   for(int n = 0; n < currentVoice->allOscs[oscInd]->p0ModProc.sources.size(); ++n)
                   {
                       juce::String checkAgainst = currentVoice->allOscs[oscInd]->p0ModProc.sources[n]->sourceId;
                       if(sourceId == checkAgainst)
                       {
                           currentVoice->allOscs[oscInd]->p0ModProc.sources[n]->setDepth(value);
                       }
                   }
                   
               }
                else if(destId == "p1Dest")
                {
                    for(int n = 0; n < currentVoice->allOscs[oscInd]->p1ModProc.sources.size(); ++n)
                    {
                        juce::String checkAgainst = currentVoice->allOscs[oscInd]->p1ModProc.sources[n]->sourceId;
                        if(sourceId == checkAgainst)
                        {
                            currentVoice->allOscs[oscInd]->p1ModProc.sources[n]->setDepth(value);
                        }
                    }
                    
                }
                else if(destId == "nDest")
                {
                    for(int n = 0; n < currentVoice->allOscs[oscInd]->nModProc.sources.size(); ++n)
                    {
                        juce::String checkAgainst = currentVoice->allOscs[oscInd]->nModProc.sources[n]->sourceId;
                        if(sourceId == checkAgainst)
                        {
                            currentVoice->allOscs[oscInd]->nModProc.sources[n]->setDepth(value);
                        }
                    }
                    
                }
            }
        }
    }
}
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SpectrumTable1AudioProcessor();
}



