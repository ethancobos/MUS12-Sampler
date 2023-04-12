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
    mAttackS.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mAttackS.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(mAttackS);
    
    mAttackL.setFont(10.0f);
    mAttackL.setText("Attack", juce::NotificationType::dontSendNotification);
    mAttackL.setJustificationType(juce::Justification::centredTop);
    mAttackL.attachToComponent(&mAttackS, false);
    
    mAttackAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                          "AMPATTACK",
                                                                                          mAttackS);
    
    mDecayS.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mDecayS.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(mDecayS);
    
    mDecayL.setFont(10.0f);
    mDecayL.setText("Decay", juce::NotificationType::dontSendNotification);
    mDecayL.setJustificationType(juce::Justification::centredTop);
    mDecayL.attachToComponent(&mDecayS, false);
    
    mDecayAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                          "AMPDECAY",
                                                                                          mDecayS);
    
    mSustainS.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mSustainS.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(mSustainS);
    
    mSustainL.setFont(10.0f);
    mSustainL.setText("Sustain", juce::NotificationType::dontSendNotification);
    mSustainL.setJustificationType(juce::Justification::centredTop);
    mSustainL.attachToComponent(&mSustainS, false);
    
    mSustainAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                          "AMPSUSTAIN",
                                                                                          mSustainS);
    
    mReleaseS.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mReleaseS.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(mReleaseS);
    
    mReleaseL.setFont(10.0f);
    mReleaseL.setText("Release", juce::NotificationType::dontSendNotification);
    mReleaseL.setJustificationType(juce::Justification::centredTop);
    mReleaseL.attachToComponent(&mReleaseS, false);
    
    mReleaseAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                          "AMPRELEASE",
                                                                                          mReleaseS);

}

AmplitudeEnvelope::~AmplitudeEnvelope()
{
}

void AmplitudeEnvelope::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void AmplitudeEnvelope::resized()
{
    const auto startx = 0.0f;
    const auto startY = 0.1f;
    const auto width = 0.25f;
    const auto height = 0.9f;
    
    mAttackS.setBoundsRelative(startx, startY, width, height);
    mDecayS.setBoundsRelative(startx + width, startY, width, height);
    mSustainS.setBoundsRelative(startx + (2 * width), startY, width, height);
    mReleaseS.setBoundsRelative(startx + (3 * width), startY, width, height);
}
