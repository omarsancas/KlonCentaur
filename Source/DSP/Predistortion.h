/*
  ==============================================================================

    Predistortion.h
    Created: 20 May 2023 12:03:02pm
    Author:  Omar Sanchez

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Predistortion
{
public:
    
    Predistortion();
    
    ~Predistortion();
    
    void process (juce::AudioBuffer<float>& buffer);
    void prepare (juce::dsp::ProcessSpec spec);
    
private:
    
    juce::dsp::StateVariableTPTFilter<float> hpFilter;
    
};



