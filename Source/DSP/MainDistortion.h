/*
  ==============================================================================

    MainDistortion.h
    Created: 20 May 2023 12:03:34pm
    Author:  Omar Sanchez

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"


class MainDistortion
{
public:
    
    MainDistortion();
    
    ~MainDistortion();
    
    void process (juce::AudioBuffer<float>& buffer, int numChannels, float mDrive);
    void prepare (juce::dsp::ProcessSpec spec);
    float calculateDeJongMap (float x);
    float getTanhOf (const float input);
    
    
private:
    
    juce::dsp::Oversampling<float> oversamplingProcessor;
    juce::Random random, whiteNoise;
};
