/*
  ==============================================================================

    Predistortion.cpp
    Created: 20 May 2023 12:03:02pm
    Author:  Omar Sanchez

  ==============================================================================
*/

#include "Predistortion.h"


Predistortion::Predistortion()
{
    
}

Predistortion::~Predistortion()
{
    
}

void Predistortion::process (juce::AudioBuffer<float>& buffer)
{
    auto audioBlock = juce::dsp::AudioBlock<float> (buffer);
    auto context = juce::dsp::ProcessContextReplacing<float> (audioBlock);
    hpFilter.process(context);
}


void Predistortion::prepare(juce::dsp::ProcessSpec spec)
{
    hpFilter.prepare(spec);
    hpFilter.reset();
    hpFilter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
    hpFilter.setCutoffFrequency(175.0f);
    hpFilter.setResonance(1.0f);
}
