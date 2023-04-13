/*
  ==============================================================================

    customSamplerVoice.cpp
    Created: 13 Apr 2023 11:13:09am
    Author:  Ethan Cobos

  ==============================================================================
*/

#include "customSamplerVoice.h"


void customSamplerVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);
    juce::dsp::AudioBlock<float>              block (outputBuffer);
    juce::dsp::ProcessContextReplacing<float> context  (block);
    mainChain.process (context);
}

void customSamplerVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = outputChannels;
    mainChain.prepare(spec);
    mainChain.reset();
    isPrepared = true;
}

void customSamplerVoice::updatefilter(float freq, float res, float sampleRate)
{
    *mainChain.get<0>().state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, freq, res);
}
