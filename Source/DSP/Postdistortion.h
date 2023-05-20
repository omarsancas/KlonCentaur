/*
  ==============================================================================

    Postdistortion.h
    Created: 20 May 2023 12:03:23pm
    Author:  Omar Sanchez

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Postdistortion
{
public:
    
    Postdistortion();
    
    ~Postdistortion();
    
    void process (juce::AudioBuffer<float>& buffer);
    void prepare (juce::dsp::ProcessSpec spec);
    void updateHSFilter(const float &gain);
    
private:
    
    juce::dsp::LadderFilter<float> lpFilter;
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> hsFilter;
    float lpFilterCutoff = 4000.0f;
    float sampleRate;
    
};
