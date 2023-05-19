/*
  ==============================================================================

    Filters.cpp
    Created: 19 May 2023 5:10:50pm
    Author:  Omar Sanchez

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


void KlonCentaurAudioProcessor::updateHSFilter(const float &gain){
    
    *hsFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighShelf(lastSampleRate, 1000.0f, 1.0f, gain);
    
}

void KlonCentaurAudioProcessor::prepareFilters(juce::dsp::ProcessSpec spec)
{
    lpFilter.prepare(spec);
    lpFilter.reset();
    lpFilter.setEnabled(true);
    lpFilter.setMode(juce::dsp::LadderFilterMode::LPF12);
    lpFilter.setCutoffFrequencyHz(lpFilterCutoff);
    lpFilter.setResonance(0.0f);
    lpFilter.setDrive(1.0f);
    
    hpFilter.prepare(spec);
    hpFilter.reset();
    hpFilter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
    hpFilter.setCutoffFrequency(175.0f);
    hpFilter.setResonance(1.0f);
    
    hsFilter.prepare(spec);
    hsFilter.reset();
    updateHSFilter(pow(10, *apvts.getRawParameterValue("Tone") / 20));

}
