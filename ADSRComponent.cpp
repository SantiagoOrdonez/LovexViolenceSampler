/*
  ==============================================================================

    ADSRComponent.cpp
    Created: 14 May 2020 2:02:14am
    Author:  santi

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ADSRComponent.h"

//==============================================================================
ADSRComponent::ADSRComponent(LovexViolenceSamplerAudioProcessor& p): processor (p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    attackKnob.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    attackKnob.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 40, 20);
    attackKnob.setColour(Slider::ColourIds::thumbColourId, Colours::red);
    addAndMakeVisible(attackKnob);

    attackLabel.setFont(10.0f);
    attackLabel.attachToComponent(&attackKnob, false);
    attackLabel.setText("Attack", dontSendNotification);
    attackLabel.setJustificationType(Justification::centredTop);

    attackAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "ATTACK", attackKnob);


    decayKnob.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    decayKnob.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 40, 20);
    decayKnob.setColour(Slider::ColourIds::thumbColourId, Colours::red);
    addAndMakeVisible(decayKnob);

    decayLabel.setFont(10.0f);
    decayLabel.attachToComponent(&decayKnob, false);
    decayLabel.setText("Decay", dontSendNotification);
    decayLabel.setJustificationType(Justification::centredTop);

    decayAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "DECAY", decayKnob);


    sustainKnob.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    sustainKnob.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 40, 20);
    sustainKnob.setColour(Slider::ColourIds::thumbColourId, Colours::red);
    addAndMakeVisible(sustainKnob);

    sustainLabel.setFont(10.0f);
    sustainLabel.attachToComponent(&sustainKnob, false);
    sustainLabel.setText("Sustain", dontSendNotification);
    sustainLabel.setJustificationType(Justification::centredTop);

    sustainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "SUSTAIN", sustainKnob);

    releaseKnob.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    releaseKnob.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 40, 20);
    releaseKnob.setColour(Slider::ColourIds::thumbColourId, Colours::red);
    addAndMakeVisible(releaseKnob);

    releaseLabel.setFont(10.0f);
    releaseLabel.attachToComponent(&sustainKnob, false);
    releaseLabel.setText("Release", dontSendNotification);
    releaseLabel.setJustificationType(Justification::centredTop);

    releaseAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "RELEASE", releaseKnob);

}

ADSRComponent::~ADSRComponent()
{
}

void ADSRComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("ADSRComponent", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void ADSRComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    const auto startX = 0.6f;
    const auto startY = 0.2f;
    const auto knobWidth = 0.1f;
    const auto knobHeight = 0.75f;

    attackKnob.setBoundsRelative(startX, startY, knobWidth, knobHeight);
    decayKnob.setBoundsRelative(startX + knobWidth, startY, knobHeight, knobHeight);
    sustainKnob.setBoundsRelative(startX + knobWidth*2, startY, knobHeight, knobHeight);
    releaseKnob.setBoundsRelative(startX + knobWidth*3, startY, knobHeight, knobHeight);
}
