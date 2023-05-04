/*
  ==============================================================================

    InputBuffer.h
    Created: 3 May 2023 7:54:40pm
    Author:  Omar Sanchez

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class InputBuffer
{
public:
    
    InputBuffer();
    
    ~InputBuffer();
    
    void process (juce::AudioBuffer<float>& buffer);
    
private:
    
};
