/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LovexViolenceSamplerAudioProcessorEditor::LovexViolenceSamplerAudioProcessorEditor (LovexViolenceSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    loadButton.onClick = [&]() { processor.loadFile(); };
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

    if (processor.getNumSamplerSounds() > 0) {
        Path p;
        audioPoints.clear();
        auto waveform = processor.getWaveform();
        auto ratio = waveform.getNumSamples() / getWidth();
        auto buffer = waveform.getReadPointer(0);

        for (int sample = 0; sample < waveform.getNumSamples(); sample += ratio)
        {
            audioPoints.push_back(buffer[sample]);
        }
        p.startNewSubPath(0, getHeight() / 2);
        for (int sample = 0; sample < audioPoints.size(); sample += 1) {
            auto point = jmap<float>(audioPoints[sample], -1.0f, 1.0f, 200, 0);
            p.lineTo(sample, point);
        }
        g.strokePath(p, PathStrokeType(2));
    }
}

void LovexViolenceSamplerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    //loadButton.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 50, 100, 100);
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