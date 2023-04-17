/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "WaveFormThumbnail.h"
#include "AmplitudeEnvelope.h"
#include "OutputGain.h"
#include "SamplerFilter.h"
#include "SamplerCompresh.h"

//==============================================================================
/**
*/
class MUS_12_SamplerAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                            public juce::Timer
{
public:
    MUS_12_SamplerAudioProcessorEditor (MUS_12_SamplerAudioProcessor&);
    ~MUS_12_SamplerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    //========================== My Functions ======================================
    void timerCallback() override;

private:
    
    MUS_12_SamplerAudioProcessor& audioProcessor;
    WaveFormThumbnail mWaveThumbnail;
    AmplitudeEnvelope mAmpEnv;
    OutputGain mGain;
    SamplerFilter mFilter;
    SamplerCompresh mCompresh;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MUS_12_SamplerAudioProcessorEditor)
};
