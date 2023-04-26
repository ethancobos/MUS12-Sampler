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
    cutoffS.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    addAndMakeVisible(&cutoffS);
    cutoffAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                         audioProcessor.filterFreq,
                                                                                         cutoffS);
       
    resonanceS.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    resonanceS.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(&resonanceS);
    resonanceAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                            audioProcessor.filterRes,
                                                                                            resonanceS);
    
    gainS.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    gainS.setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 20);
    addAndMakeVisible(gainS);
    
    gainAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                       audioProcessor.filterGain,
                                                                                       gainS);
    
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
    
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::buttonMouseOverBackgroundColourId));
    g.fillRoundedRectangle(5.0f, 5.0f, getWidth() - 10.0f, getHeight() - 15.0f, 10.0f);
    
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::labelTextColourId));
    g.setFont(juce::Font("Ableton Sans Medium", (getHeight() / 5) - 5.0f, juce::Font::plain));
    g.drawFittedText("FILTER", 5.0f, 5.0f, getWidth() - 10.0f, (getHeight() / 5), juce::Justification::centred, 1);
    
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::separatorColourId));
    g.fillRoundedRectangle(10.0f, yStart, getWidth() - 20.0f, getHeight() - yStart - 15.0f, 10.0f);
}

void SamplerFilter::resized()
{
    const auto startX = 10.0f;
    const auto startY = (getHeight() / 5) + 5.0f;
    const auto width = (getWidth() - 25.0f) / 3;
    const auto height = (getHeight() - startY - 15.0f) / 3;
    const auto buttonW = getHeight() / 12.5;
    
    cutoffS.setBounds(startX, startY, width, height * 2);
    resonanceS.setBounds(startX + width, startY, width, height * 2);
    filterMenu.setBounds(startX + (2 * width) + 5.0f, startY + 10.0f, width - 10.0f, height / 2);

    gainS.setBounds(startX, startY + (2 * height), getWidth() - 25.0f, height);
    
    filterBypass.setSize(buttonW, buttonW);
    filterBypass.setCentrePosition(getHeight() / 10 + 5, getHeight() / 10 + 5);
    
}
