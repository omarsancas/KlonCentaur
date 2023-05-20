/*
  ==============================================================================

    Filters.cpp
    Created: 19 May 2023 5:10:50pm
    Author:  Omar Sanchez

  ==============================================================================
*/

#include "PluginProcessor.h"


void KlonCentaurAudioProcessor::updateHSFilter(const float &gain){
    
//    *hsFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighShelf(lastSampleRate, 1000.0f, 1.0f, gain);
    
}

void KlonCentaurAudioProcessor::prepareFilters(juce::dsp::ProcessSpec spec)
{
    updateHSFilter(pow(10, *apvts.getRawParameterValue("Tone") / 20));
}
