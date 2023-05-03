/*
  ==============================================================================

    Level.h
    Created: 2 May 2023 7:13:52pm
    Author:  Omar Sanchez

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Level
{
public:
    
    Level();
    
    ~Level();
    
    void process (juce::AudioBuffer<float>& buffer, float gainValue);
    
private:
    
};
