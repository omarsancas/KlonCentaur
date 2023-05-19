/*
  ==============================================================================

    Drive.cpp
    Created: 19 May 2023 5:10:42pm
    Author:  Omar Sanchez

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


void KlonCentaurAudioProcessor::updateDrive(const float &drive){
    
    mDrive = drive + 4;
    
}

void KlonCentaurAudioProcessor::prepareDrive()
{
    updateDrive(*apvts.getRawParameterValue("Gain"));

}

float KlonCentaurAudioProcessor::getTanhOf(const float input)
{
    return tanh(input);
}

float KlonCentaurAudioProcessor::convertToDrive(const float drive)
{
    return pow(10, drive / 20);
}
