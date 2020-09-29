/*
  ==============================================================================

    ModSourceComponent.cpp
    Created: 25 Sep 2020 11:25:38am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "ModSourceComponent.h"

//==============================================================================
ModSourceComponent::ModSourceComponent(juce::String desc, juce::DragAndDropContainer* parentContainer) : parent(parentContainer), description(desc)
{
    //printf("Component %s created\n", desc.toUTF16());
}

void ModSourceComponent::paint (juce::Graphics& g)
{
    juce::Rectangle<float> area = getLocalBounds().toFloat();
    g.setColour(ringColor);
    g.fillEllipse(area);
    g.setColour(centerColor);
    g.fillEllipse(area.reduced(5.0));
}

void ModSourceComponent::resized()
{

}

LfoComponent::LfoComponent(juce::String desc, juce::DragAndDropContainer* parentContainer, int index) : modSource(desc, parentContainer), LfoIndex(index)
{
    addAndMakeVisible(&modSource);
    addAndMakeVisible(&freqSlider);
    addAndMakeVisible(&waveform);
    
    freqSlider.setSliderStyle(juce::Slider::Rotary);
    freqSlider.setRange(0.01f, 20.0f); //range goes into very low audio rate
    freqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    freqSlider.setSkewFactorFromMidPoint(1.5);
    freqSlider.setNumDecimalPlacesToDisplay(0);
    
    waveform.addItem("Sine", 1);
    waveform.addItem("Saw", 2);
    waveform.addItem("Triangle", 3);
    waveform.addItem("Square", 4);
    waveform.setSelectedItemIndex(1);
    waveform.setEditableText(false);
    
}

void LfoComponent::paint(juce::Graphics &g)
{
    juce::Colour background = color.RGBColor(50, 55, 55);
    g.fillAll(background);
    juce::Rectangle<float> area = getLocalBounds().toFloat();
    juce::Colour outlineColor = color.RGBColor(210, 210, 210);
    g.setColour(outlineColor);
    g.drawRect(area, 1.5f);
}

void LfoComponent::resized()
{
    int n = getHeight() / 10;
    modSource.setBounds(2.5 * n, n, 2 * n,  2 * n);
    freqSlider.setBounds(n, 4.65 * n, 5 * n, 5 * n);
    waveform.setBounds(5 * n, 1.5 * n, 5 * n, 1.5 * n);
    
}


