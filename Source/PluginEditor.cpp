/*
  ==============================================================================
    This file contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MUS_12_SamplerAudioProcessorEditor::MUS_12_SamplerAudioProcessorEditor (MUS_12_SamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), mWaveThumbnail(p), mAmpEnv(p), mGain(p), mFilter(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(mWaveThumbnail);
    addAndMakeVisible(mAmpEnv);
    addAndMakeVisible(mGain);
    addAndMakeVisible(mFilter);
    startTimerHz(30);
    setSize (900, 600);
}

MUS_12_SamplerAudioProcessorEditor::~MUS_12_SamplerAudioProcessorEditor()
{
    stopTimer();
}

//==============================================================================
void MUS_12_SamplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::blue);
    g.setColour(juce::Colours::white);
    
}

void MUS_12_SamplerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    mWaveThumbnail.setBoundsRelative(0.1f, 0.1f, 0.8f, 0.3f);
    mAmpEnv.setBoundsRelative(0.01f, 0.5f, 0.3f, 0.3f);
    mGain.setBoundsRelative(0.35f, 0.5f, (0.3f / 4.0f), 0.3f);
    mFilter.setBounds(450.0f, 300.0f, 200.0f, 200.0f);
}

void MUS_12_SamplerAudioProcessorEditor::timerCallback()
{
    repaint();
}
