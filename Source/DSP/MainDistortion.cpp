/*
  ==============================================================================

    MainDistortion.cpp
    Created: 20 May 2023 12:03:34pm
    Author:  Omar Sanchez

  ==============================================================================
*/

#include "MainDistortion.h"


MainDistortion::MainDistortion(): oversamplingProcessor (2, 1, juce::dsp::Oversampling<float>::FilterType::filterHalfBandPolyphaseIIR, true, false)
{
    
}

MainDistortion::~MainDistortion()
{
    
}

void MainDistortion::process (juce::AudioBuffer<float>& buffer, int numChannels, float mDrive)
{
    
    juce::dsp::AudioBlock<float> audioBlock {buffer};
    
    auto upSampledBlock = oversamplingProcessor.processSamplesUp(audioBlock);
    
    // Main loop with distortion
    
    float deJongSample;
    float randomNum;
    
    for (int sample = 0; sample < upSampledBlock.getNumSamples(); ++sample){
        
        for (int channel = 0; channel < numChannels; ++channel){

            float* data = upSampledBlock.getChannelPointer(channel);

            float x = data[sample];
            
            deJongSample = calculateDeJongMap(x);
            
            randomNum = std::ceil(deJongSample * 100.0) / 100.0 + deJongSample * 0.01f;
            
            const float drive = mDrive + randomNum * 0.1f;
            
            data[sample] = getTanhOf(-drive * x + x) - getTanhOf(pow(x, 3.0f)) * 0.55f;
        }
    }
    
    oversamplingProcessor.processSamplesDown(audioBlock);
}


void MainDistortion::prepare(juce::dsp::ProcessSpec spec)
{
    oversamplingProcessor.initProcessing(spec.maximumBlockSize);
    oversamplingProcessor.reset();
}



float MainDistortion::calculateDeJongMap(float x)
{
    
    float white = whiteNoise.nextFloat() - 0.5f;
        
    float b0 = 0.99765 + white * 0.0990460;
    float b1 = 0.96300 + white * 0.2965164;
    float b2 = 0.57000 + white * 1.0526913;
    float pink = b0 + b1 + b2 + white * 0.1848;
    
    float a = 4.1f;
    float b = -4.8f;
    float output;
    
    output = sin(sin(a * x) * x) - cos(sin(b * x) * x) + pink;
    
    x = output * 0.01f;
    
    return output;
}



float MainDistortion::getTanhOf(const float input)
{
    return tanh(input);
}
