/*
  ==============================================================================

    AmplitudeEnvelope.cpp
    Created: 9 Apr 2023 5:43:18pm
    Author:  Ethan Cobos

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AmplitudeEnvelope.h"

//==============================================================================
AmplitudeEnvelope::AmplitudeEnvelope(MUS_12_SamplerAudioProcessor& p) : audioProcessor(p)
{
    mAttackS.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mAttackS.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    mAttackS.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(mAttackS);
    
    mAttackL.setText("Attack", juce::NotificationType::dontSendNotification);
    mAttackL.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(mAttackL);
    
    mAttackAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                          audioProcessor.ampAttack,
                                                                                          mAttackS);
    
    mDecayS.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDecayS.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    mDecayS.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(mDecayS);
    
    mDecayL.setText("Decay", juce::NotificationType::dontSendNotification);
    mDecayL.setJustificationType(juce::Justification::centredBottom);
    addAndMakeVisible(mDecayL);
    
    mDecayAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                         audioProcessor.ampDecay,
                                                                                          mDecayS);
    
    mSustainS.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mSustainS.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    mSustainS.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(mSustainS);
    
    mSustainL.setText("Sustain", juce::NotificationType::dontSendNotification);
    mSustainL.setJustificationType(juce::Justification::centredBottom);
    addAndMakeVisible(mSustainL);
    
    mSustainAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                           audioProcessor.ampSustain,
                                                                                          mSustainS);
    
    mReleaseS.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mReleaseS.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    mReleaseS.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(mReleaseS);
    
    mReleaseL.setText("Release", juce::NotificationType::dontSendNotification);
    mReleaseL.setJustificationType(juce::Justification::centredBottom);
    addAndMakeVisible(mReleaseL);
    
    mReleaseAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                           audioProcessor.ampRelease,
                                                                                          mReleaseS);
}

AmplitudeEnvelope::~AmplitudeEnvelope()
{
}

void AmplitudeEnvelope::paint (juce::Graphics& g)
{
    float yStart = (getHeight() / 5) + 5.0f;
    
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::buttonMouseOverBackgroundColourId));
    g.fillRoundedRectangle(10.0f, 5.0f, getWidth() - 15.0f, getHeight() - 10.0f, 10.0f);
    
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::labelTextColourId));
    g.setFont(juce::Font("Ableton Sans Medium", (getHeight() / 5) - 5.0f, juce::Font::plain));
    g.drawFittedText("AMP ENV", 15.0f, 5.0f, getWidth() - 25.0f, (getHeight() / 5), juce::Justification::centred, 1);
    
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::separatorColourId));
    g.fillRoundedRectangle(15.0f, yStart, getWidth() - 25.0f, getHeight() - yStart - 10.0f, 10.0f);
}

void AmplitudeEnvelope::resized()
{
    const auto startX = 15.0f;
    const auto startY = (getHeight() / 5) + 5.0f;
    const auto width = (getWidth() - 25.0f) / 2;
    const auto height = (getHeight() - startY - 15.0f) / 2;
    const auto height4th = height / 4;
    
    mAttackS.setBounds(startX, startY + height4th, width, height4th * 3);
    mAttackL.setBounds(startX, startY + (height4th / 4), width, height4th);
    mAttackL.setFont(height / 5);
    
    mDecayS.setBounds(startX + width, startY + height4th, width, height4th * 3);
    mDecayL.setBounds(startX + width, startY + (height4th / 4), width, height4th);
    mDecayL.setFont(height / 5);
    
    mSustainS.setBounds(startX, startY + height + height4th, width, height4th * 3);
    mSustainL.setBounds(startX, startY + height + (height4th / 4), width, height4th);
    mSustainL.setFont(height / 5);
    
    mReleaseS.setBounds(startX + width, startY + height + height4th, width, height4th * 3);
    mReleaseL.setBounds(startX + width, startY + height + (height4th / 4), width, height4th);
    mReleaseL.setFont(height / 5);
}
