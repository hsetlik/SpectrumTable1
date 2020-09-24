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
    juce::String p0Id = "p0Param";
    juce::String p0Name = "Parameter 0";
    juce::String nId = "nParam";
    juce::String nName = "number of harmonics";
    juce::String p1Id = "p1Param";
    juce::String p1Name = "Parameter 2";
    juce::String algId = "algParam";
    juce::String algName = "Serial Amplitude Modulation";
    
    layout.add(std::make_unique<juce::AudioParameterFloat>(nId, nName, 1.0, 40.0, 6.0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(p0Id, p0Name, 0.0, 15.0, 1.0));
    layout.add(std::make_unique<juce::AudioParameterFloat>(p1Id, p1Name, 1.0, 15.0, 1.0));
    layout.add(std::make_unique<juce::AudioParameterBool>(algId, algName, false));
    
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
    for(int i = 0; i < 15; ++i)
    {
        std::unique_ptr<juce::AudioBuffer<float>> newBuffer(new juce::AudioBuffer<float>(1, 512));
        scopeSource.addBuffer(*newBuffer);
    }
    scopeSource.relevantBuffers.shrink_to_fit();
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
    scopeSource.sampleRate = rate;
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
    scopeSource.bufferSize = buffer.getNumSamples();
    for(int i = 0; i < synth.getNumVoices(); ++i)
    {
        if((thisVoice =  dynamic_cast<SpectrumVoice*>(synth.getVoice(i))))
        {
            thisVoice->setNumHarmonics(tree.getRawParameterValue("nParam"));
            thisVoice->setVoiceP0(tree.getRawParameterValue("p0Param"));
            thisVoice->setVoiceP1(tree.getRawParameterValue("p1Param"));
            thisVoice->setAlgChoice(tree.getRawParameterValue("algParam"));
            if(thisVoice->isVoiceActive())
                scopeSource.fundamental = thisVoice->osc.fundamental;
        }
    }
    buffer.clear();
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    scopeSource.addBuffer(buffer);
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

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SpectrumTable1AudioProcessor();
}
