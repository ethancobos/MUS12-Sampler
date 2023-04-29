/*
  ==============================================================================

    SamplerDistortion.cpp
    Created: 21 Apr 2023 5:18:11pm
    Author:  Ethan Cobos

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SamplerDistortion.h"

//==============================================================================
SamplerDistortion::SamplerDistortion(MUS_12_SamplerAudioProcessor& p) : audioProcessor(p)
{
    gainS.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(gainS);
    
    gainL.setText("Gain", juce::NotificationType::dontSendNotification);
    gainL.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(gainL);
    
    gainAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                        audioProcessor.distGain,
                                                                                          gainS);
    
    driveS.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(driveS);
    
    driveL.setText("Drive", juce::NotificationType::dontSendNotification);
    driveL.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(driveL);
    
    driveAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                        audioProcessor.distDrive,
                                                                                          driveS);
    
    rangeS.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(rangeS);
    
    rangeL.setText("Range", juce::NotificationType::dontSendNotification);
    rangeL.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(rangeL);
    
    rangeAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                        audioProcessor.distRange,
                                                                                          rangeS);
    
    blendS.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    addAndMakeVisible(blendS);
    
    blendL.setText("Blend", juce::NotificationType::dontSendNotification);
    blendL.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(blendL);
    
    blendAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                        audioProcessor.distBlend,
                                                                                        blendS);
    
    addAndMakeVisible(&distBypass);
    bypassAtach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.getAPVTS(),
                                                                                         audioProcessor.distBypass,
                                                                                         distBypass);
}

SamplerDistortion::~SamplerDistortion()
{
}

void SamplerDistortion::paint (juce::Graphics& g)
{
    float yStart = (getHeight() / 5) + 5.0f;
    
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::buttonMouseOverBackgroundColourId));
    g.fillRoundedRectangle(10.0f, 5.0f, getWidth() - 15.0f, getHeight() - 15.0f, 10.0f);
    
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::labelTextColourId));
    g.setFont(juce::Font("Ableton Sans Medium", (getHeight() / 5) - 5.0f, juce::Font::plain));
    g.drawFittedText("DISTORTION", getHeight() / 10 + 5, 5.0f, getWidth() - (getHeight() / 10 + 10), (getHeight() / 5), juce::Justification::centred, 1);
    
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::separatorColourId));
    g.fillRoundedRectangle(15.0f, yStart, getWidth() - 25.0f, getHeight() - yStart - 15.0f, 10.0f);
}

void SamplerDistortion::resized()
{
    const auto startX = 15.0f;
    const auto startY = (getHeight() / 5) + 10.0f;
    const auto width = (getWidth() - 30.0f);
    const auto height = (getHeight() - startY - 15.0f) / 4;
    const auto buttonW = getHeight() / 12.5;
    
    driveS.setBounds(startX, startY, width, height);
    driveL.setBounds(startX, startY, width, height / 3);
    driveS.setTextBoxStyle(juce::Slider::TextBoxRight, false, 65, 20);
    driveL.setFont(height / 3);
    
    rangeS.setBounds(startX, startY + height, width, height);
    rangeL.setBounds(startX, startY + height, width, height / 3 + 2);
    rangeL.setFont(height / 3);
    rangeS.setTextBoxStyle(juce::Slider::TextBoxRight, false, 65, 20);
    
    blendS.setBounds(startX, startY + (2 * height), width, height);
    blendL.setBounds(startX, startY + (2 * height), width, height / 3);
    blendL.setFont(height / 3);
    blendS.setTextBoxStyle(juce::Slider::TextBoxRight, false, 65, 20);
    
    gainS.setBounds(startX, startY + (3 * height), width, height);
    gainL.setBounds(startX, startY + (3 * height), width, height / 3);
    gainL.setFont(height / 3);
    gainS.setTextBoxStyle(juce::Slider::TextBoxRight, false, 65, 20);
    gainS.setTextValueSuffix (" dB");
    
    distBypass.setSize(buttonW, buttonW);
    distBypass.setCentrePosition(getHeight() / 10 + 10, getHeight() / 10 + 5);
    
}
