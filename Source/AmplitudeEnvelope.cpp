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
    mAttackS.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    addAndMakeVisible(mAttackS);
    
//    mAttackL.setFont(10.0f);
//    mAttackL.setText("Attack", juce::NotificationType::dontSendNotification);
//    mAttackL.setJustificationType(juce::Justification::centredTop);
//    mAttackL.attachToComponent(&mAttackS, false);
    
    mAttackAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                          audioProcessor.ampAttack,
                                                                                          mAttackS);
    
    mDecayS.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDecayS.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    addAndMakeVisible(mDecayS);
    
//    mDecayL.setFont(10.0f);
//    mDecayL.setText("Decay", juce::NotificationType::dontSendNotification);
//    mDecayL.setJustificationType(juce::Justification::centredTop);
//    mDecayL.attachToComponent(&mDecayS, false);
    
    mDecayAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                         audioProcessor.ampDecay,
                                                                                          mDecayS);
    
    mSustainS.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mSustainS.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    addAndMakeVisible(mSustainS);
    
//    mSustainL.setFont(10.0f);
//    mSustainL.setText("Sustain", juce::NotificationType::dontSendNotification);
//    mSustainL.setJustificationType(juce::Justification::centredTop);
//    mSustainL.attachToComponent(&mSustainS, false);
    
    mSustainAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                           audioProcessor.ampSustain,
                                                                                          mSustainS);
    
    mReleaseS.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mReleaseS.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    addAndMakeVisible(mReleaseS);
    
//    mReleaseL.setFont(10.0f);
//    mReleaseL.setText("Release", juce::NotificationType::dontSendNotification);
//    mReleaseL.setJustificationType(juce::Justification::centredTop);
//    mReleaseL.attachToComponent(&mReleaseS, false);
    
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
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::separatorColourId));
    g.fillRoundedRectangle(15.0f, yStart, getWidth() - 25.0f, getHeight() - yStart - 10.0f, 10.0f);
}

void AmplitudeEnvelope::resized()
{
    const auto startX = 15.0f;
    const auto startY = (getHeight() / 5) + 5.0f;
    const auto width = (getWidth() - 25.0f) / 2;
    const auto height = (getHeight() - startY - 15.0f) / 2;
    
    mAttackS.setBounds(startX, startY, width, height);
    mDecayS.setBounds(startX + width, startY, width, height);
    mSustainS.setBounds(startX, startY + height, width, height);
    mReleaseS.setBounds(startX + width, startY + height, width, height);
}
