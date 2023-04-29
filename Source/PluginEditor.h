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
#include "CustomGUI.h"
#include "SamplerDistortion.h"

using namespace juce;

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
    
    float fullWidth = 1000.0f;
    float fullHeight = 500.0f;
    float one6th = 1.0f / 6.0f;
    float one12th = 1.0f / 12.0f;
    float one3rd = 1.0f / 3.0f;
    
    MUS_12_SamplerAudioProcessor& audioProcessor;
    WaveFormThumbnail mWaveThumbnail;
    AmplitudeEnvelope mAmpEnv;
    OutputGain mGain;
    SamplerFilter mFilter;
    SamplerCompresh mCompresh;
    SamplerDistortion mDist;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MUS_12_SamplerAudioProcessorEditor)
};
