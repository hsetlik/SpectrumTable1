/*
  ==============================================================================

    ModSourceComponent.cpp
    Created: 25 Sep 2020 11:25:38am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ModSourceComponent.h"

//==============================================================================
ModSourceComponent::ModSourceComponent(juce::String desc, juce::DragAndDropContainer* parentContainer) :  parent(parentContainer), description(desc)
{
    printf("Component %s created\n", desc.toUTF16());
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
    juce::Rectangle<int> area = getLocalBounds();
    setBounds(area);
}

LfoComponent::LfoComponent(juce::String desc, juce::DragAndDropContainer* parentContainer, int index) : modSource(desc, parentContainer), LfoIndex(index)
{
    addAndMakeVisible(&modSource);
    addAndMakeVisible(& freqSlider);
    freqSlider.setSliderStyle(juce::Slider::Rotary);
    freqSlider.setRange(0.01f, 20.0f); //range goes into very low audio rate
    freqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    freqSlider.setNumDecimalPlacesToDisplay(0);
    
}

void LfoComponent::resized()
{
    int n = getHeight() / 10;
    modSource.setBounds(n, n, 3 * n, 3 * n);
    freqSlider.setBounds(n, 5 * n, 3 * n, 3 * n);
}
