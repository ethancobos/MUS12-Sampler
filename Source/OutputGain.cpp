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
    mGainS.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(mGainS);
    
    mGainL.setFont(10.0f);
    mGainL.setText("Gain", juce::NotificationType::dontSendNotification);
    mGainL.setJustificationType(juce::Justification::centredTop);
    mGainL.attachToComponent(&mGainS, false);
    
    mGainAtach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(),
                                                                                        audioProcessor.outputGain,
                                                                                          mGainS);
}

OutputGain::~OutputGain()
{
}

void OutputGain::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void OutputGain::resized()
{
    const auto startx = 0.0f;
    const auto startY = 0.1f;
    const auto width = 1.0f;
    const auto height = 0.9f;
    
    mGainS.setBoundsRelative(startx, startY, width, height);
}
