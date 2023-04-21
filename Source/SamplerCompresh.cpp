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
    
    threshL.setText("Threshhold", juce::NotificationType::dontSendNotification);
    threshL.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(threshL);
    
    threshAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                         audioProcessor.compThresh,
                                                                                         threshS);
    
    ratioS.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ratioS.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    ratioS.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&ratioS);
    
    ratioL.setText("Ratio", juce::NotificationType::dontSendNotification);
    ratioL.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(ratioL);
    
    ratioAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                        audioProcessor.compRatio,
                                                                                        ratioS);
    
    attackS.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    attackS.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    attackS.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&attackS);
    
    attackL.setText("Attack", juce::NotificationType::dontSendNotification);
    attackL.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(attackL);
    
    attackAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                        audioProcessor.compAttack,
                                                                                         attackS);
    
    releaseS.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    releaseS.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    releaseS.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&releaseS);
    
    releaseL.setText("Release", juce::NotificationType::dontSendNotification);
    releaseL.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(releaseL);
    
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
    
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::labelTextColourId));
    g.setFont(juce::Font("Ableton Sans Medium", (getHeight() / 5) - 5.0f, juce::Font::plain));
    g.drawFittedText("COMPRESSION", 10.0f, 5.0f, getWidth() - 25.0f, (getHeight() / 5), juce::Justification::centred, 1);
    
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::separatorColourId));
    g.fillRoundedRectangle(10.0f, yStart, getWidth() - 25.0f, getHeight() - yStart - 15.0f, 10.0f);
}

void SamplerCompresh::resized()
{
    const auto startX = 10.0f;
    const auto startY = (getHeight() / 5) + 5.0f;
    const auto width = (getWidth() - 25.0f) / 3;
    const auto height = (getHeight() - startY - 15.0f) / 2;
    const auto height4th = height / 4;
    
    threshS.setBounds(startX, startY + height4th, width, height4th * 3);
    threshL.setBounds(startX, startY + (height4th / 4), width, height4th);
    threshL.setFont(height / 5);
    
    ratioS.setBounds(startX + width, startY + height4th, width, height4th * 3);
    ratioL.setBounds(startX + width, startY + (height4th / 4), width, height4th);
    ratioL.setFont(height / 5);
    
    
    attackS.setBounds(startX, startY + height + height4th, width, height4th * 3);
    attackL.setBounds(startX, startY + height + (height4th / 4), width, height4th);
    attackL.setFont(height / 5);
    
    releaseS.setBounds(startX + width, startY + height + height4th, width, height4th * 3);
    releaseL.setBounds(startX + width, startY + height + (height4th / 4), width, height4th);
    releaseL.setFont(height / 5);
}
