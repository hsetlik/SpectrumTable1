/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SpectrumTable1AudioProcessorEditor::SpectrumTable1AudioProcessorEditor (SpectrumTable1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor(p), scope(&audioProcessor.scopeSource)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
    addAndMakeVisible(&scope);
    addAndMakeVisible(&sliderSet);
    sliderSet.attachToTree(&audioProcessor.tree);
   
}

SpectrumTable1AudioProcessorEditor::~SpectrumTable1AudioProcessorEditor()
{
}

//==============================================================================
void SpectrumTable1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    
}

void SpectrumTable1AudioProcessorEditor::resized()
{
    int n = getWidth() / 16;
    sliderSet.setBounds(0, 0, 10 * n, 6 * n);
    scope.setBounds(3 * n, 5.5 * n, 8 * n, 6 * n);
}
