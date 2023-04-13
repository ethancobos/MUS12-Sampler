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
    customSamplerVoice();
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void updatefilter(float freq, float res, float sampleRate);
    
private:
    
//    using mGain = juce::dsp::Gain<float>;
    mFilter lowPassFilter;
};

