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
    filterMenu.setJustificationType(juce::Justification::centred);
    filterMenu.addItem("Low Pass", 1);
    filterMenu.addItem("High Pass", 3);
    addAndMakeVisible(&filterMenu);
    menuAtach = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.getAPVTS(),
                                                                                         audioProcessor.filterCoice,
                                                                                         filterMenu);
       
    cutoffS.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    cutoffS.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    cutoffS.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&cutoffS);
    cutoffAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                         audioProcessor.filterFreq,
                                                                                         cutoffS);
       
    resonanceS.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    resonanceS.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    resonanceS.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&resonanceS);
    resonanceAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                            audioProcessor.filterRes,
                                                                                            resonanceS);
    
    addAndMakeVisible(&filterBypass);
    bypassAtach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.getAPVTS(),
                                                                                         audioProcessor.filterBypass,
                                                                                         filterBypass);
    
    cutoffS.setSkewFactorFromMidPoint(1000.0f);
}

SamplerFilter::~SamplerFilter()
{
}

void SamplerFilter::paint (juce::Graphics& g)
{
    float yStart = (getHeight() / 5) + 5.0f;
    
    //background ui stuff
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::buttonMouseOverBackgroundColourId));
    g.fillRoundedRectangle(5.0f, 5.0f, getWidth() - 10.0f, getHeight() - 15.0f, 10.0f);
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::separatorColourId));
    g.fillRoundedRectangle(10.0f, yStart, getWidth() - 20.0f, getHeight() - yStart - 15.0f, 10.0f);
    g.drawText("Cutoff", 46, 70, 50, 25, juce::Justification::centredLeft);
    g.drawText("Resonance", 107, 70, 70, 25, juce::Justification::centredLeft);
}

void SamplerFilter::resized()
{
    //need to come back and dynamically set these...ok for now
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    
    filterMenu.setBounds(area.removeFromTop(20));
    cutoffS.setBounds (30, 90, 70, 70);
    resonanceS.setBounds (100, 90, 70, 70);
    filterBypass.setBounds(5, 5, 50, 50);
    
}
