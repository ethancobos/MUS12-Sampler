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
public:
    CustomGUI();
    
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
    
private:
    inline void applyThreeColourScheme();
    const static Colour accentC;
    const static Colour textC;
    const static Colour backgroundC;
    const static Colour foregroundC;
};

}
