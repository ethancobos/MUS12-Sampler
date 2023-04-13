/*
  ==============================================================================

    SamplerFilter.cpp
    Created: 12 Apr 2023 3:26:29pm
    Author:  Ethan Cobos

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SamplerFilter.h"

//==============================================================================
SamplerFilter::SamplerFilter(MUS_12_SamplerAudioProcessor& p) : audioProcessor(p)
{
    cutoffS.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    cutoffS.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(cutoffS);
    
    cutoffL.setFont(10.0f);
    cutoffL.setText("Cutoff", juce::NotificationType::dontSendNotification);
    cutoffL.setJustificationType(juce::Justification::centredTop);
    cutoffL.attachToComponent(&cutoffS, false);
    
    cutoffAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                         audioProcessor.filterFreq,
                                                                                         cutoffS);
    
    resonanceS.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    resonanceS.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(resonanceS);
    
    resonanceL.setFont(10.0f);
    resonanceL.setText("Resonance", juce::NotificationType::dontSendNotification);
    resonanceL.setJustificationType(juce::Justification::centredTop);
    resonanceL.attachToComponent(&resonanceS, false);
    
    resonanceAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                            audioProcessor.filterRes,
                                                                                            resonanceS);
}

SamplerFilter::~SamplerFilter()
{
}

void SamplerFilter::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void SamplerFilter::resized()
{
    const auto startx = 0.0f;
    const auto startY = 0.1f;
    const auto width = 0.25f;
    const auto height = 0.9f;
    
    cutoffS.setBoundsRelative(startx, startY, width, height);
    resonanceS.setBoundsRelative(startx + width, startY, width, height);
}
