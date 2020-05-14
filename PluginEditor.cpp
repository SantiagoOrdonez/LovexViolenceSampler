/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SampleVisualizer.h"

//==============================================================================
LovexViolenceSamplerAudioProcessorEditor::LovexViolenceSamplerAudioProcessorEditor (LovexViolenceSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    sampleVisualizer = new SampleVisualizer(p);
    addAndMakeVisible(*sampleVisualizer);
    adsrComponent = new ADSRComponent(p);
    addAndMakeVisible(*adsrComponent);

    

    loadButton.onClick = [&]() { processor.loadFile();};
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 200);
    addAndMakeVisible(loadButton);
}

LovexViolenceSamplerAudioProcessorEditor::~LovexViolenceSamplerAudioProcessorEditor()
{
}

//==============================================================================
void LovexViolenceSamplerAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    g.setFont(15.0f);
}

void LovexViolenceSamplerAudioProcessorEditor::resized()
{

    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    loadButton.setBounds(10, 10, 50, 50);
}

bool LovexViolenceSamplerAudioProcessorEditor::isInterestedInFileDrag(const StringArray& files) {
    for (auto file : files) {
        if (file.contains(".wav") || file.contains(".aif") || file.contains(".mp3")) {
            return true;
        }
    }
    return false;
}

void LovexViolenceSamplerAudioProcessorEditor::filesDropped(const StringArray& files, int x, int y) {
    for (auto file : files) {
        if (isInterestedInFileDrag(file)) {
            processor.loadFile(file);
        }
    }
    repaint();
}