/*
  ==============================================================================

    Gain.cpp
    Created: 19 May 2023 5:30:44pm
    Author:  Omar Sanchez

  ==============================================================================
*/

#include "../../PluginProcessor.h"
#include "../../PluginEditor.h"

void KlonCentaurAudioProcessor::prepareGains(juce::dsp::ProcessSpec spec)
{
    lastPreampGain = pow(10, *apvts.getRawParameterValue("Input") / 20);
    currentPreampGain = pow(10, *apvts.getRawParameterValue("Input") / 20);
    
    lastTrimGain = pow(10, *apvts.getRawParameterValue("Trim") / 20);
    currentTrimGain = pow(10, *apvts.getRawParameterValue("Trim") / 20);
    
}
