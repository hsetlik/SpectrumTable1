/*
  ==============================================================================

    RGBColor.h
    Created: 27 Sep 2020 8:44:00am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

struct ColorCreator
{
    juce::Colour fromRGB(int r, int g, int b)
    {
        return juce::Colour(juce::uint8(r), juce::uint8(g), juce::uint8(b), juce::uint8(255));
    }
    juce::Colour fromRGB(int r, int g, int b, int a)
    {
        return juce::Colour(juce::uint8(r), juce::uint8(g), juce::uint8(b), juce::uint8(a));
    }
    juce::Colour blend(juce::Colour colorA, juce::Colour colorB, float ratio)
    {
        float redA = colorA.getFloatRed();
    }
}
