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
    
    pedalHousingImage = juce::ImageFileFormat::loadFrom (BinaryData::pedalHousing_png, BinaryData::pedalHousing_pngSize);
    pedalHousingComponent.setImage (pedalHousingImage);
    addAndMakeVisible (pedalHousingComponent);
    
    prepareSliders();
    setLookAndFeel (&myLookAndFeel);
    
    setSize (600, 400);
}

KlonCentaurAudioProcessorEditor::~KlonCentaurAudioProcessorEditor()
{
    GainSlider.removeListener (this);
    inputSlider.removeListener(this);
    setLookAndFeel (nullptr);
}

void KlonCentaurAudioProcessorEditor::prepareSliders()
{
    GainSlider.setSliderStyle  (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    GainSlider.setTextBoxStyle (juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0.0f, 0.0f);
    GainSlider.addListener     (this);
    addAndMakeVisible             (GainSlider);
    
    
    inputSlider.setSliderStyle  (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    inputSlider.setTextBoxStyle (juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0.0f, 0.0f);
    inputSlider.addListener     (this);
    addAndMakeVisible             (inputSlider);
    
    
    toneSlider.setSliderStyle  (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    toneSlider.setTextBoxStyle (juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0.0f, 0.0f);
    toneSlider.addListener     (this);
    addAndMakeVisible             (toneSlider);
    
    
    outputSlider.setSliderStyle  (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    outputSlider.setTextBoxStyle (juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0.0f, 0.0f);
    outputSlider.addListener     (this);
    addAndMakeVisible             (outputSlider);
    
    inputAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.apvts, "Input", inputSlider);
    gainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.apvts, "Trim", GainSlider);
    toneAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.apvts, "Tone", toneSlider);
    outputAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.apvts, "Output", outputSlider);
}

//==============================================================================
void KlonCentaurAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::whitesmoke);
}

void KlonCentaurAudioProcessorEditor::resized()
{
    backgroundComponent.setBounds (getLocalBounds ());
    pedalHousingComponent.setBounds (0, 0, getWidth(), getHeight());
    
    toneSlider.setBounds (getWidth()/2.5, 45, 45, 45);
    inputSlider.setBounds (getWidth()/2.5 + 75, 45, 45, 45);
    
    GainSlider.setBounds (getWidth()/2.5, 120, 45, 45);
    outputSlider.setBounds (getWidth()/2.5 + 75, 120, 45, 45);
}



void KlonCentaurAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    if (slider == &GainSlider)
        DBG ("Gain: " << GainSlider.getValue());
    
    if (slider == &toneSlider)
        DBG ("Tone: " << toneSlider.getValue());
    
    
    if (slider == &inputSlider)
        DBG ("Input: " << inputSlider.getValue());
    
    
    if (slider == &outputSlider)
        DBG ("Output: " << outputSlider.getValue());
    
}
