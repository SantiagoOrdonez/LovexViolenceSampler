/*
  ==============================================================================

    ADSRComponent.h
    Created: 14 May 2020 2:02:14am
    Author:  santi

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class ADSRComponent    : public Component
{
public:
    ADSRComponent(LovexViolenceSamplerAudioProcessor& p);
    ~ADSRComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    Slider attackKnob, decayKnob, sustainKnob, releaseKnob;
    Label attackLabel, decayLabel, sustainLabel, releaseLabel;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;

    LovexViolenceSamplerAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRComponent)
};
