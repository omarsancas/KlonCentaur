/*
  ==============================================================================

    Gain.h
    Created: 5 May 2023 12:11:53pm
    Author:  Omar Sanchez

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Gain
{
public:
    
    Gain();
    
    ~Gain();
    
    void process (juce::AudioBuffer<float>& buffer, float gainValue);
    
private:
    
};
