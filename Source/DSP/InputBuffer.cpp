/*
  ==============================================================================

    InputBuffer.cpp
    Created: 3 May 2023 7:54:40pm
    Author:  Omar Sanchez

  ==============================================================================
*/

#include "InputBuffer.h"

InputBuffer::InputBuffer()
{
    
}

InputBuffer::~InputBuffer()
{
    
}

void InputBuffer::process (juce::AudioBuffer<float>& buffer)
{
    const auto numSamples = buffer.getNumSamples();
    
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        auto* x = buffer.getWritePointer (channel);

               // Input buffer
               juce::FloatVectorOperations::multiply (x, 0.5f, numSamples);      
               juce::FloatVectorOperations::clip (x, x, -4.5f, 4.5f, numSamples); // op amp clipping
    }
}
