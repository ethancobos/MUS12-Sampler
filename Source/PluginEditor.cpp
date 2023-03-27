/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MUS_12_SamplerAudioProcessorEditor::MUS_12_SamplerAudioProcessorEditor (MUS_12_SamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    mLoadFileButton.onClick = [&](){ audioProcessor.loadFile(); };
    addAndMakeVisible(mLoadFileButton);
    
    setSize (200, 200);
}

MUS_12_SamplerAudioProcessorEditor::~MUS_12_SamplerAudioProcessorEditor()
{
}

//==============================================================================
void MUS_12_SamplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void MUS_12_SamplerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    mLoadFileButton.setBounds(getWidth() / 2 - 50, getWidth() / 2 - 50, 100, 100);
    
}
