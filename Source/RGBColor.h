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
        float redB = colorB.getFloatRed();
        float fNewRed = (((1.0 - ratio) * redA) + (ratio * redB)) / 2.0f;
        
        float greenA = colorA.getFloatGreen();
        float greenB = colorB.getFloatGreen();
        float fNewGreen = (((1.0 - ratio) * greenA) + (ratio * greenB)) / 2.0f;
        
        float blueA = colorA.getFloatBlue();
        float blueB = colorB.getFloatBlue();
        float fNewBlue = (((1.0 - ratio) * blueA) + (ratio * blueB)) / 2.0f;
        
        float alphaA = colorA.getFloatAlpha();
        float alphaB = colorB.getFloatAlpha();
        float fNewAlpha = (((1.0 - ratio) * alphaA) + (ratio * alphaB)) / 2.0f;
        
        int iR = floor(fNewRed * 255);
        int iG = floor(fNewGreen * 255);
        int iB = floor(fNewBlue * 255);
        int iA = floor(fNewAlpha * 255);
        
        return fromRGB(iR, iG, iB, iA);
    }
};
