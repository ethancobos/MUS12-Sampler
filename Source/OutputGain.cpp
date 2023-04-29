/*
  ==============================================================================

    OutputGain.cpp
    Created: 14 Apr 2023 5:00:45pm
    Author:  Ethan Cobos

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OutputGain.h"

//==============================================================================
OutputGain::OutputGain(MUS_12_SamplerAudioProcessor& p) : audioProcessor(p)
{
    mGainS.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    addAndMakeVisible(mGainS);
    
    mGainAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                        audioProcessor.outputGain,
                                                                                          mGainS);
}

OutputGain::~OutputGain()
{
}

void OutputGain::paint (juce::Graphics& g)
{
    float yStart = (getHeight() / 5) + 5.0f;
    
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::buttonMouseOverBackgroundColourId));
    g.fillRoundedRectangle(5.0f, 5.0f, getWidth() - 15.0f, getHeight() - 10.0f, 10.0f);
    
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::labelTextColourId));
    g.setFont(juce::Font("Ableton Sans Medium", (getHeight() / 5) - 5.0f, juce::Font::plain));
    g.drawFittedText("GAIN", 10.0f, 5.0f, getWidth() - 25.0f, (getHeight() / 5), juce::Justification::centred, 1);
    
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::separatorColourId));
    g.fillRoundedRectangle(10.0f, yStart, getWidth() - 25.0f, getHeight() - yStart - 10.0f, 10.0f);
}

void OutputGain::resized()
{
    const auto startX = 10.0f;
    const auto startY = (getHeight() / 5) + 5.0f;
    const auto width = getWidth() - 25.0f;
    const auto height = getHeight() - startY - 15.0f;
    
    mGainS.setBounds(startX, startY, width, height);
    mGainS.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    mGainS.setTextValueSuffix(" dB");
}
