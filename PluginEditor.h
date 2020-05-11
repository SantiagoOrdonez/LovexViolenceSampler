/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class LovexViolenceSamplerAudioProcessorEditor  : public AudioProcessorEditor, 
                                                  public FileDragAndDropTarget
{
public:
    LovexViolenceSamplerAudioProcessorEditor (LovexViolenceSamplerAudioProcessor&);
    ~LovexViolenceSamplerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LovexViolenceSamplerAudioProcessor& processor;
    std::vector<float> audioPoints; 
    TextButton loadButton{ "Load" };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LovexViolenceSamplerAudioProcessorEditor)
};
