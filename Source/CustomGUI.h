/*
  ==============================================================================

    CustomGUI.h
    Created: 16 Apr 2023 11:23:41pm
    Author:  Ethan Cobos

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace juce {

class CustomGUI : public juce::LookAndFeel_V4
{
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
    
};

class CustomDial : public Slider
{
public:
    CustomDial(){
        setSliderStyle(SliderStyle::RotaryHorizontalVerticalDrag);
        setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::orange);
        setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::orange);
    }
    
private:
    
    
};

}
