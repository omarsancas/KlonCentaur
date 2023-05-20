/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DSP/Level.h"
#include "DSP/InputBuffer.h"
#include "DSP/Gain.h"
#include "DSP/Predistortion.h"
#include "DSP/Postdistortion.h"
#include "DSP/MainDistortion.h"

//==============================================================================
/**
*/
class KlonCentaurAudioProcessor  : public juce::AudioProcessor, juce::AudioProcessorValueTreeState::Listener
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    KlonCentaurAudioProcessor();
    ~KlonCentaurAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    void updateDrive(const float &drive);
    
    float convertToDrive(const float drive);
    
    float getTanhOf(const float input);
    
    float getRandomNumber(float timeElapsed);
    
    float calculateDeJongMap(float x);
    
    void prepareFilters(juce::dsp::ProcessSpec spec);
    
    void prepareGains(juce::dsp::ProcessSpec spec);
    
    void prepareDrive();
    
    void updateHSFilter(const float &gain);
    
    void callPreOSChain(juce::dsp::AudioBlock<float> block);
    
    void callPostOSChain(juce::dsp::AudioBlock<float> block);
    
    void callProcessorCore(juce::dsp::AudioBlock<float> block, const int numChannels);
    //==============================================================================
    
    
    juce::AudioProcessorValueTreeState apvts;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    
    float lastSampleRate {44100.0f};
    float mDrive {-4.0f};
    float randomNumber = 0.69f;
    
private:
    Gain input;
    Gain output;
    Level level;
    InputBuffer inputBuffer;
    Predistortion predistortion;
    Postdistortion postdistortion;
    MainDistortion maindistortion;
    
    float lastPreampGain, currentPreampGain, lastTrimGain, currentTrimGain;    
    
    
//    juce::dsp::LadderFilter<float> lpFilter;
//    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> hsFilter;
//    juce::dsp::StateVariableTPTFilter<float> hpFilter;
    


    
    void parameterChanged (const juce::String& parameterID, float newValue) override;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KlonCentaurAudioProcessor)
};
