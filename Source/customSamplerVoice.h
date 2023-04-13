/*
  ==============================================================================

    customSamplerVoice.h
    Created: 13 Apr 2023 11:13:09am
    Author:  Ethan Cobos

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "customSamplerSound.h"

class customSamplerVoice : public juce::SamplerVoice
{
public:
    
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void updatefilter(float freq, float res, float sampleRate);
private:
    
    using mFilter = juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>>;
    juce::dsp::ProcessorChain<mFilter> mainChain;
    bool isPrepared { false };
};

