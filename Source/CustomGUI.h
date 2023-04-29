/*
  ==============================================================================

    CustomGUI.h
    Created: 16 Apr 2023 11:23:41pm
    Author:  Ethan Cobos

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

using namespace juce;

class CustomGUI : public juce::LookAndFeel_V4, public DeletedAtShutdown
{
public:
    CustomGUI();
    ~CustomGUI();
    
    void drawToggleButton (Graphics& g, ToggleButton& button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
    
    void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                                           float sliderPos,
                                           float minSliderPos,
                                           float maxSliderPos,
                           const Slider::SliderStyle style, Slider& slider) override;
    
    JUCE_DECLARE_SINGLETON(CustomGUI, true)
    
private:
    inline void applyThreeColourScheme();
    const static Colour accentC;
    const static Colour textC;
    const static Colour backgroundC;
    const static Colour foregroundC;
};
