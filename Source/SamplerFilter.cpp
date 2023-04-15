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
    cutoffS.setSkewFactorFromMidPoint(1000.0f);
}

SamplerFilter::~SamplerFilter()
{
}

void SamplerFilter::paint (juce::Graphics& g)
{
    //background ui stuff
    juce::Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.fillAll (juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Filter", titleArea, juce::Justification::centredTop);
    g.drawText("Cutoff", 46, 70, 50, 25, juce::Justification::centredLeft);
    g.drawText("Resonance", 107, 70, 70, 25, juce::Justification::centredLeft);
    
    juce::Rectangle <float> area (25, 25, 150, 150);
    
    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void SamplerFilter::resized()
{
    //need to come back and dynamically set these...ok for now
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    
    filterMenu.setBounds(area.removeFromTop(20));
    cutoffS.setBounds (30, 90, 70, 70);
    resonanceS.setBounds (100, 90, 70, 70);
}
