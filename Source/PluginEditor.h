/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MUS_12_SamplerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MUS_12_SamplerAudioProcessorEditor (MUS_12_SamplerAudioProcessor&);
    ~MUS_12_SamplerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    juce::TextButton mLoadFileButton { "testing" };
    
    MUS_12_SamplerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MUS_12_SamplerAudioProcessorEditor)
};
