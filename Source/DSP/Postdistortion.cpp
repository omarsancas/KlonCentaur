/*
  ==============================================================================

    Postdistortion.cpp
    Created: 20 May 2023 12:03:23pm
    Author:  Omar Sanchez

  ==============================================================================
*/

#include "Postdistortion.h"


Postdistortion::Postdistortion()
{
    
}

Postdistortion::~Postdistortion()
{
    
}

void Postdistortion::process (juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> audioBlock {buffer};
    lpFilter.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    
    hsFilter.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}


void Postdistortion::prepare(juce::dsp::ProcessSpec spec)
{
    lpFilter.prepare(spec);
    lpFilter.reset();
    lpFilter.setEnabled(true);
    lpFilter.setMode(juce::dsp::LadderFilterMode::LPF12);
    lpFilter.setCutoffFrequencyHz(lpFilterCutoff);
    lpFilter.setResonance(0.0f);
    lpFilter.setDrive(1.0f);
    
    
    hsFilter.prepare(spec);
    hsFilter.reset();
    
    sampleRate = spec.sampleRate;
}


void Postdistortion::updateHSFilter(const float &gain){
    
    *hsFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, 1000.0f, 1.0f, gain);
    
}
