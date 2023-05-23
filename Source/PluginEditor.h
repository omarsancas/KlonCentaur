/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "LookAndFeel/LookAndFeel.h"

//==============================================================================
/**
*/
class KlonCentaurAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener
{
public:
    KlonCentaurAudioProcessorEditor (KlonCentaurAudioProcessor&);
    ~KlonCentaurAudioProcessorEditor() override;

    //==============================================================================
//    void sliderValueChanged (juce::Slider* slider) override;
    void paint (juce::Graphics&) override;
    void resized() override;
    void prepareSliders();
    void sliderValueChanged (juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    KlonCentaurAudioProcessor& audioProcessor;
    
    juce::Slider GainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttach;
    
    
    MyLookAndFeel myLookAndFeel;
    
    juce::Image backgroundImage;
    juce::ImageComponent backgroundComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KlonCentaurAudioProcessorEditor)
};
