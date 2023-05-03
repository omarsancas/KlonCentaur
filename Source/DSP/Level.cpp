/*
  ==============================================================================

    Level.cpp
    Created: 2 May 2023 7:13:52pm
    Author:  Omar Sanchez

  ==============================================================================
*/

#include "Level.h"

Level::Level()
{
    
}

Level::~Level()
{
    
}

void Level::process (juce::AudioBuffer<float>& buffer, float gainValue)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float x = buffer.getSample (channel, i);
            
            float y = x * gainValue;
            
            buffer.setSample (channel, i, y);
        }
    }
}
