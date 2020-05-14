/*
  ==============================================================================

    SampleVisualizer.cpp
    Created: 14 May 2020 12:48:45am
    Author:  santi

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SampleVisualizer.h"

//==============================================================================
SampleVisualizer::SampleVisualizer(LovexViolenceSamplerAudioProcessor& p) : processor (p)
{
    setSize(getWidth(), getHeight() / 2);

}

SampleVisualizer::~SampleVisualizer()
{
}

void SampleVisualizer::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.setColour(Colours::yellowgreen);
    g.drawRect(getLocalBounds(), 1);
    if (processor.getNumSamplerSounds() > 0) {
        Path p;
        audioPoints.clear();
        auto waveform = processor.getWaveform();
        auto ratio = waveform.getNumSamples() / getWidth();
        auto buffer = waveform.getReadPointer(0);

        for (int sample = 0; sample < waveform.getNumSamples(); sample += ratio) {
            audioPoints.push_back(buffer[sample]);
        }
        p.startNewSubPath(0, getHeight() / 2);
        for (int sample = 0; sample < audioPoints.size(); sample += 1) {
            auto point = jmap<float>(audioPoints[sample], -1.0f, 1.0f, getHeight(), 0);
            p.lineTo(sample, point);
        }
        g.setColour(Colours::white);
        g.strokePath(p, PathStrokeType(2));
    }
}

void SampleVisualizer::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
