/*
  ==============================================================================
    This file contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;

//==============================================================================
MUS_12_SamplerAudioProcessorEditor::MUS_12_SamplerAudioProcessorEditor (MUS_12_SamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), mWaveThumbnail(p), mAmpEnv(p), mGain(p), mFilter(p), mCompresh(p)
{
    juce::LookAndFeel::setDefaultLookAndFeel(&customGUI);
    addAndMakeVisible(mWaveThumbnail);
    addAndMakeVisible(mAmpEnv);
    addAndMakeVisible(mGain);
    addAndMakeVisible(mFilter);
    addAndMakeVisible(mCompresh);
    startTimerHz(30);
    setSize (fullWidth, fullHeight);
}

MUS_12_SamplerAudioProcessorEditor::~MUS_12_SamplerAudioProcessorEditor()
{
    stopTimer();
    juce::LookAndFeel::setDefaultLookAndFeel(nullptr);
}

//==============================================================================
void MUS_12_SamplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void MUS_12_SamplerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    mWaveThumbnail.setBoundsRelative(one6th, one12th, 2 * one3rd, one3rd);
    mAmpEnv.setBoundsRelative(0.0f, 0.0f, one6th, 0.5f);
    mFilter.setBoundsRelative(one3rd, 0.5f, one3rd, 0.5f);
    mCompresh.setBoundsRelative(one3rd * 2, 0.5f, one3rd, 0.5f);
    mGain.setBoundsRelative(one6th * 5, 0.0f, one6th, 0.5f);
}

void MUS_12_SamplerAudioProcessorEditor::timerCallback()
{
    repaint();
}

