/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KlonCentaurAudioProcessor::KlonCentaurAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
                    apvts (*this, nullptr, "Parameters", createParameters())                    
#endif
{
//    apvts.addParameterListener ("Input", this);
    apvts.addParameterListener ("Gain", this);
    apvts.addParameterListener ("Tone", this);
    apvts.addParameterListener ("Trim", this);
}

KlonCentaurAudioProcessor::~KlonCentaurAudioProcessor()
{
//    apvts.addParameterListener ("Input", this);
    apvts.addParameterListener ("Gain", this);
    apvts.addParameterListener ("Tone", this);
    apvts.addParameterListener ("Trim", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout KlonCentaurAudioProcessor::createParameters()
{
//    juce::AudioProcessorValueTreeState::ParameterLayout parameters;
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> parameters;
    
//    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "Input", 1 }, "Input", 0.0f, 1.0f, 0.5f));
//
//
//    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "Level", 1 }, "Level", 0.0f, 1.0f, 0.5f));
//
//    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "Gain", 1 }, "Gain", 0.0f, 1.0f, 0.5f));
//
//
//    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "Trim", 1 }, "Trim", 0.0f, 1.0f, 0.5f));
//
//
//    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "Tone", 1 }, "Tone", 0.0f, 1.0f, 0.5f));
//
//    return parameters;
    
    parameters.reserve(4);
    
    auto inputParam = std::make_unique<juce::AudioParameterFloat>("Input", "Input", 0.0f, 2.0f, 1.0f);
    auto driveParam = std::make_unique<juce::AudioParameterFloat>("Trim", "Trim", 0.0f, 12.0f, 0.0f);
    auto toneParam = std::make_unique<juce::AudioParameterFloat>("Tone", "Tone", 20.0f, 200.0f, 20.0f);
    auto trimParam = std::make_unique<juce::AudioParameterFloat>("Output", "Output", 0.0f, 2.0f, 1.0f);

    parameters.push_back(std::move(inputParam));
    parameters.push_back(std::move(driveParam));
    parameters.push_back(std::move(toneParam));
    parameters.push_back(std::move(trimParam));
    
    return { parameters.begin(), parameters.end() };
}

//==============================================================================
const juce::String KlonCentaurAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool KlonCentaurAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool KlonCentaurAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool KlonCentaurAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double KlonCentaurAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int KlonCentaurAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int KlonCentaurAudioProcessor::getCurrentProgram()
{
    return 0;
}

void KlonCentaurAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String KlonCentaurAudioProcessor::getProgramName (int index)
{
    return {};
}

void KlonCentaurAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void KlonCentaurAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();
    
    lastSampleRate = sampleRate;
    
    predistortion.prepare(spec);
    postdistortion.prepare(spec);
    prepareFilters(spec);
    prepareGains(spec);
    prepareDrive();
    
    maindistortion.prepare(spec);
    
}

void KlonCentaurAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool KlonCentaurAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void KlonCentaurAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    const auto numChannels = buffer.getNumChannels();
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
//    float levelValue   = apvts.getRawParameterValue ("Level")->load();
//
    float inputValue   = apvts.getRawParameterValue ("Input")->load();
    float outputValue   = apvts.getRawParameterValue ("Output")->load();
    float toneValue = apvts.getRawParameterValue("Tone")->load();
    float trimeValue = apvts.getRawParameterValue("Trim")->load();
//
//    inputBuffer.process(buffer);
//    level.process(buffer, levelValue);
    input.process(buffer, inputValue);
    
    predistortion.process(buffer);

    maindistortion.process(buffer, numChannels, trimeValue);
    
    // Post distortion DSP
//    callPostOSChain(audioBlock);
    postdistortion.updateHSFilter(toneValue);
    postdistortion.process(buffer);
    
    // Trim gain and smoothing
    
    output.process(buffer, outputValue);
}

//==============================================================================
bool KlonCentaurAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* KlonCentaurAudioProcessor::createEditor()
{
    return new KlonCentaurAudioProcessorEditor (*this);
}

//==============================================================================
void KlonCentaurAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void KlonCentaurAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}


void KlonCentaurAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue){
    
//    if (parameterID == "Tone") {
//
//        updateHSFilter(pow(10, newValue / 2 / 20));
//        lpFilter.setCutoffFrequencyHz(pow(10, newValue / 20) * lpFilterCutoff);
//
//    } else if (parameterID == "Trim"){
//
//        currentTrimGain = pow(10, newValue / 20);
//
//    } else if (parameterID == "Gain"){
//
//        updateDrive(newValue);
//
//    } else {
//        currentPreampGain = pow(10, newValue / 20);
//    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KlonCentaurAudioProcessor();
}
