/*
  ==============================================================================

    Gain.cpp
    Created: 5 May 2023 12:11:53pm
    Author:  Omar Sanchez

  ==============================================================================
*/

#include "Gain.h"

Gain::Gain()
{
    
}

Gain::~Gain()
{
    
}

void Gain::process (juce::AudioBuffer<float>& buffer, float gainValue)
{
//    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
//    {
//        for (int i = 0; i < buffer.getNumSamples(); i++)
//        {
//            float x = buffer.getSample (channel, i);
//
//            float y = x * gainValue;
//
//            buffer.setSample (channel, i, y);
//        }
//    }

    
    if (gainValue == lastPreampGain)
    {
        buffer.applyGain(0, buffer.getNumSamples(), gainValue);

    } else
    {
        buffer.applyGainRamp(0, buffer.getNumSamples(), lastPreampGain, gainValue);
        lastPreampGain = gainValue;
    }
}
