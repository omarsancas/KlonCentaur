/*
  ==============================================================================

    LookAndFeel.h
    Created: 22 May 2023 5:09:39pm
    Author:  Omar Sanchez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class MyLookAndFeel : public juce::LookAndFeel_V4
{
public:
    
    MyLookAndFeel()
    {
        knobImage = juce::ImageCache::getFromMemory (BinaryData::knobf_png, BinaryData::knobf_pngSize);
        setColour (juce::Label::ColourIds::textColourId, juce::Colours::black);
    }
    
    ~MyLookAndFeel() { }
    
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPosProportional,
                           const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override
    {
        // FILM STRIP
        const int numFrames = knobImage.getHeight() / knobImage.getWidth();
        const int frameIndex = (int) std::ceil (sliderPosProportional * (numFrames - 1));
        
        const float radius = fmin (width*0.5, height*0.5);
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;
        
        g.drawImage (knobImage,
                     rx,
                     ry,
                     2 * radius,
                     2 * radius,
                     0,
                     frameIndex * knobImage.getWidth(),
                     knobImage.getWidth(),
                     knobImage.getWidth());
    }
    
private:
    
    juce::Image knobImage;
    
};
