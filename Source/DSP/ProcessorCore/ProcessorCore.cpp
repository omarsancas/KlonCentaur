/*
  ==============================================================================

    ProcessorCore.cpp
    Created: 19 May 2023 5:19:00pm
    Author:  Omar Sanchez

  ==============================================================================
*/

#include "../../PluginProcessor.h"
#include "../../PluginEditor.h"


void KlonCentaurAudioProcessor::callProcessorCore(juce::dsp::AudioBlock<float> block, const int numChannels)
{
    float deJongSample;
    float randomNum;
    
    for (int sample = 0; sample < block.getNumSamples(); ++sample){
        
        for (int channel = 0; channel < numChannels; ++channel){

            float* data = block.getChannelPointer(channel);

            float x = data[sample];
            
            deJongSample = calculateDeJongMap(x);
            
            randomNum = std::ceil(deJongSample * 100.0) / 100.0 + deJongSample * 0.01f;
            
            const float drive = mDrive + randomNum * 0.1f;
            
            data[sample] = getTanhOf(-drive * x + x) - getTanhOf(pow(x, 3.0f)) * 0.55f;
        }
    }
}
