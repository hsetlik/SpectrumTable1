/*
  ==============================================================================

    ModDestination.h
    Created: 25 Sep 2020 1:05:12pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ModDestination  : public juce::Component, public juce::DragAndDropTarget
{
public:
    ModDestination();
    ~ModDestination() override;
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModDestination)
};
