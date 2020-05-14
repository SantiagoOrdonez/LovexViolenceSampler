/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LovexViolenceSamplerAudioProcessor::LovexViolenceSamplerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), APVTS (*this, nullptr, "parameters", createParameterLayout())
#endif
{
    formatManager.registerBasicFormats();
    for (int i = 0; i < samplerVoices; i++) {
        sampler.addVoice(new SamplerVoice());
    }
}

LovexViolenceSamplerAudioProcessor::~LovexViolenceSamplerAudioProcessor()
{
}

//==============================================================================
const String LovexViolenceSamplerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LovexViolenceSamplerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LovexViolenceSamplerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LovexViolenceSamplerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LovexViolenceSamplerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LovexViolenceSamplerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LovexViolenceSamplerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LovexViolenceSamplerAudioProcessor::setCurrentProgram (int index)
{
}

const String LovexViolenceSamplerAudioProcessor::getProgramName (int index)
{
    return {};
}

void LovexViolenceSamplerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void LovexViolenceSamplerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    updateADSR();
    sampler.setCurrentPlaybackSampleRate(sampleRate);
}

void LovexViolenceSamplerAudioProcessor::updateADSR()
{
    adsr.attack = *APVTS.getRawParameterValue("ATTACK");
    adsr.decay = *APVTS.getRawParameterValue("DECAY");
    adsr.sustain = *APVTS.getRawParameterValue("SUSTAIN");
    adsr.release = *APVTS.getRawParameterValue("RELEASE");

    for (int i = 0; i < sampler.getNumSounds(); i++) {
        const auto sound = dynamic_cast<SamplerSound*>(sampler.getSound(i).get());
        if (sound != NULL) {
            sound->setEnvelopeParameters(getADSRParams());
        }
    }
}

void LovexViolenceSamplerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LovexViolenceSamplerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void LovexViolenceSamplerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
    sampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool LovexViolenceSamplerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* LovexViolenceSamplerAudioProcessor::createEditor()
{
    return new LovexViolenceSamplerAudioProcessorEditor (*this);
}

//==============================================================================
void LovexViolenceSamplerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void LovexViolenceSamplerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void LovexViolenceSamplerAudioProcessor::loadFile()
{
    FileChooser chooser{ "Please load a file" };
    if (chooser.browseForFileToOpen()) {
        File file = chooser.getResult();
        loadSample(file);
    }
}

void LovexViolenceSamplerAudioProcessor::loadFile(String& filePath)
{
    auto file = File(filePath);
    loadSample(file);
}

void LovexViolenceSamplerAudioProcessor::loadSample(File file) {
    sampler.clearSounds();
    formatReader = formatManager.createReaderFor(file);    
    int sampleLength = static_cast<int>(formatReader->lengthInSamples);
    waveform.setSize(1, sampleLength);
    formatReader->read(&waveform, 0, sampleLength, 0, true, false);

    BigInteger bitfield;
    bitfield.setRange(0, 128, true);
    sampler.addSound(new SamplerSound("Sample", *formatReader, bitfield, 60, getADSRParams().attack, getADSRParams().release, 10));
}
AudioProcessorValueTreeState::ParameterLayout LovexViolenceSamplerAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<AudioParameterFloat>> parameters;

    parameters.push_back(std::make_unique<AudioParameterFloat>("ATTACK", "Attack", 0.0f, 5.0f, 0.0));
    parameters.push_back(std::make_unique<AudioParameterFloat>("DECAY", "Decay", 0.0f, 3.0f, 0.2f));
    parameters.push_back(std::make_unique<AudioParameterFloat>("SUSTAIN", "Sustain", 0.0f, 1.0f, 1.0f));
    parameters.push_back(std::make_unique<AudioParameterFloat>("RELEASE", "Release", 0.0f, 5.0f, 3.0f));

    return {parameters.begin(), parameters.end()};
}

void LovexViolenceSamplerAudioProcessor::valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged, const Identifier& property)
{
    updateADSR();
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LovexViolenceSamplerAudioProcessor();
}
