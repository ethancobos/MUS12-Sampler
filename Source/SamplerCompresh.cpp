/*
  ==============================================================================

    SamplerCompresh.cpp
    Created: 17 Apr 2023 12:21:59pm
    Author:  Ethan Cobos

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SamplerCompresh.h"

//==============================================================================
SamplerCompresh::SamplerCompresh(MUS_12_SamplerAudioProcessor& p) : audioProcessor(p)
{
    threshS.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    threshS.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    threshS.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&threshS);
    threshAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                         audioProcessor.compThresh,
                                                                                         threshS);
    
    ratioS.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ratioS.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    ratioS.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&ratioS);
    ratioAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                        audioProcessor.compRatio,
                                                                                        ratioS);
    
    attackS.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    attackS.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    attackS.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&attackS);
    attackAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                        audioProcessor.compAttack,
                                                                                         attackS);
    
    releaseS.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    releaseS.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    releaseS.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&releaseS);
    releaseAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                        audioProcessor.compRelease,
                                                                                          releaseS);

}

SamplerCompresh::~SamplerCompresh()
{
}

void SamplerCompresh::paint (juce::Graphics& g)
{
    float yStart = (getHeight() / 5) + 5.0f;
    
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::buttonMouseOverBackgroundColourId));
    g.fillRoundedRectangle(5.0f, 5.0f, getWidth() - 15.0f, getHeight() - 15.0f, 10.0f);
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::separatorColourId));
    g.fillRoundedRectangle(10.0f, yStart, getWidth() - 25.0f, getHeight() - yStart - 15.0f, 10.0f);
}

void SamplerCompresh::resized()
{
    const auto startx = 0.0f;
    const auto startY = 0.0f;
    const auto width = 0.5f;
    const auto height = 0.5f;
    
    threshS.setBoundsRelative(startx, startY, width, height);
    ratioS.setBoundsRelative(startx + width, startY, width, height);
    attackS.setBoundsRelative(startx, startY + height, width, height);
    releaseS.setBoundsRelative(startx + width, startY + height, width, height);
}
