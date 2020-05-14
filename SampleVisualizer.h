/*
  ==============================================================================

    SampleVisualizer.h
    Created: 14 May 2020 12:48:45am
    Author:  santi

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class SampleVisualizer    : public Component
{
public:
    SampleVisualizer(LovexViolenceSamplerAudioProcessor& processor);
    ~SampleVisualizer();

    void paint (Graphics&) override;
    void resized() override;

private:
    LovexViolenceSamplerAudioProcessor& processor;
    std::vector<float> audioPoints;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SampleVisualizer)
};
