/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KlonCentaurAudioProcessorEditor::KlonCentaurAudioProcessorEditor (KlonCentaurAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    backgroundImage = juce::ImageFileFormat::loadFrom (BinaryData::background_png, BinaryData::background_pngSize);
    backgroundComponent.setImage (backgroundImage);
    addAndMakeVisible (backgroundComponent);
    
    prepareSliders();
    setLookAndFeel (&myLookAndFeel);
    
    setSize (600, 400);
}

KlonCentaurAudioProcessorEditor::~KlonCentaurAudioProcessorEditor()
{
    GainSlider.removeListener (this);
    setLookAndFeel (nullptr);
}

void KlonCentaurAudioProcessorEditor::prepareSliders()
{
    GainSlider.setSliderStyle  (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    GainSlider.setTextBoxStyle (juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0.0f, 0.0f);
    GainSlider.addListener     (this);
    addAndMakeVisible             (GainSlider);
    
    gainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.apvts, "Input", GainSlider);
}

//==============================================================================
void KlonCentaurAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);
    // (Our component is opaque, so we must completely fill the background with a solid colour)
//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
//
//    g.setColour (juce::Colours::white);
//    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void KlonCentaurAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    GainSlider.setBounds (getWidth()/2 + 175, 300, 90, 90);
    
    backgroundComponent.setBounds (0, 0, getWidth(), getHeight());
    GainSlider.setBounds (getWidth()/2 + 175, 300, 90, 90);
}



void KlonCentaurAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    if (slider == &GainSlider)
        DBG ("Volumen: " << GainSlider.getValue());
    
}
