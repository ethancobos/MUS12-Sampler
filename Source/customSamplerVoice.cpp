/*
  ==============================================================================

    customSamplerVoice.cpp
    Created: 13 Apr 2023 11:13:09am
    Author:  Ethan Cobos

  ==============================================================================
*/

#include "customSamplerVoice.h"

customSamplerVoice::customSamplerVoice() : lowPassFilter(juce::dsp::IIR::Coefficients <float>::makeLowPass(44100, 20000.0f, 0.1f))
{
//    *mainChain.get<0>().state = *juce::dsp::IIR::Coefficients <float>::makeLowPass(44100, 20000.0f, 0.1f);
}

void customSamplerVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    SamplerVoice::renderNextBlock(outputBuffer, startSample, numSamples);
    juce::dsp::AudioBlock<float>              block (outputBuffer);
    juce::dsp::ProcessContextReplacing<float> context  (block);
    lowPassFilter.process (context);
}

void customSamplerVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = outputChannels;
    lowPassFilter.prepare(spec);
}

void customSamplerVoice::updatefilter(float freq, float res, float sampleRate)
{
    *lowPassFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, freq, res);
}
