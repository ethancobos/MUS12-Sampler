
/*
  ==============================================================================
   This file is part of the JUCE library.
   Copyright (c) 2022 - Raw Material Software Limited
   JUCE is an open source library subject to commercial or open-source
   licensing.
   By using JUCE, you agree to the terms of both the JUCE 7 End-User License
   Agreement and JUCE Privacy Policy.
   End User License Agreement: www.juce.com/juce-7-licence
   Privacy Policy: www.juce.com/juce-privacy-policy
   Or: You may also use this code under the terms of the GPL v3 (see
   www.gnu.org/licenses).
   JUCE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.
  ==============================================================================
*/
#include <JuceHeader.h>
#include "MySamplerVoice.h"

using namespace juce;

MySamplerSound::MySamplerSound (const String& soundName,
                            AudioFormatReader& source,
                            const BigInteger& notes,
                            int midiNoteForNormalPitch,
                            double attackTimeSecs,
                            double releaseTimeSecs,
                            double maxSampleLengthSeconds)
    : name (soundName),
      sourceSampleRate (source.sampleRate),
      midiNotes (notes),
      midiRootNote (midiNoteForNormalPitch)
{
    if (sourceSampleRate > 0 && source.lengthInSamples > 0)
    {
        length = jmin ((int) source.lengthInSamples,
                       (int) (maxSampleLengthSeconds * sourceSampleRate));

        data.reset (new AudioBuffer<float> (jmin (2, (int) source.numChannels), length + 4));

        source.read (data.get(), 0, length + 4, 0, true, true);

        params.attack  = static_cast<float> (attackTimeSecs);
        params.release = static_cast<float> (releaseTimeSecs);
    }
}

MySamplerSound::~MySamplerSound()
{
}

bool MySamplerSound::appliesToNote (int midiNoteNumber)
{
    return midiNotes[midiNoteNumber];
}

bool MySamplerSound::appliesToChannel (int /*midiChannel*/)
{
    return true;
}

//==============================================================================
MySamplerVoice::MySamplerVoice() {}
MySamplerVoice::~MySamplerVoice() {}

bool MySamplerVoice::canPlaySound (SynthesiserSound* sound)
{
    return dynamic_cast<const MySamplerSound*> (sound) != nullptr;
}

void MySamplerVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound* s, int /*currentPitchWheelPosition*/)
{
    if (auto* sound = dynamic_cast<const MySamplerSound*> (s))
    {
        pitchRatio = std::pow (2.0, (midiNoteNumber - sound->midiRootNote) / 12.0)
                        * sound->sourceSampleRate / getSampleRate();

        sourceSamplePosition = 0.0;
        lgain = velocity;
        rgain = velocity;

        adsr.setSampleRate (sound->sourceSampleRate);
        adsr.setParameters (sound->params);

        adsr.noteOn();
    }
    else
    {
        jassertfalse; // this object can only play SamplerSounds!
    }
}

void MySamplerVoice::stopNote (float /*velocity*/, bool allowTailOff)
{
    if (allowTailOff)
    {
        adsr.noteOff();
    }
    else
    {
        clearCurrentNote();
        adsr.reset();
    }
}

void MySamplerVoice::pitchWheelMoved (int /*newValue*/) {}
void MySamplerVoice::controllerMoved (int /*controllerNumber*/, int /*newValue*/) {}

//==============================================================================
void MySamplerVoice::renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    if (auto* playingSound = static_cast<MySamplerSound*> (getCurrentlyPlayingSound().get()))
    {
        auto& data = *playingSound->data;
        const float* const inL = data.getReadPointer (0);
        const float* const inR = data.getNumChannels() > 1 ? data.getReadPointer (1) : nullptr;

        float* outL = outputBuffer.getWritePointer (0, startSample);
        float* outR = outputBuffer.getNumChannels() > 1 ? outputBuffer.getWritePointer (1, startSample) : nullptr;

        while (--numSamples >= 0)
        {
            auto pos = (int) sourceSamplePosition;
            auto alpha = (float) (sourceSamplePosition - pos);
            auto invAlpha = 1.0f - alpha;

            // just using a very simple linear interpolation here..
            float l = (inL[pos] * invAlpha + inL[pos + 1] * alpha);
            float r = (inR != nullptr) ? (inR[pos] * invAlpha + inR[pos + 1] * alpha)
                                       : l;

            auto envelopeValue = adsr.getNextSample();
            
            // velocity and envelope
            l *= lgain * envelopeValue;
            r *= rgain * envelopeValue;
            
            if(distNotBypassed){
                l = dist.processSample(l);
                r = dist.processSample(r);
            }
            
            // filtering
            if (filterNotBypassed){
                l = mFilter.processSample(l);
                r = mFilter.processSample(r);
            }
            
            // compression
            if (compNotBypassed){
                l = mCompressor.processSample(0, l);
                r = mCompressor.processSample(1, r);
                l = compGain.processSample(l);
                r = compGain.processSample(r);
            }

            // output gain
            l = mGain.processSample(l);
            r = mGain.processSample(r);
            
            if (outR != nullptr)
            {
                *outL++ += l;
                *outR++ += r;
            }
            else
            {
                *outL++ += (l + r) * 0.5f;
            }

            sourceSamplePosition += pitchRatio;

            if (sourceSamplePosition > playingSound->length)
            {
                stopNote (0.0f, false);
                break;
            }
        }
    }
}

void MySamplerVoice::reset()
{
    mGain.reset();
    mFilter.reset();
    mCompressor.reset();
    compGain.reset();
}

void MySamplerVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{
    reset();
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = outputChannels;
    
    mGain.prepare(spec);
    compGain.prepare(spec);
    mFilter.prepare(spec);
    mCompressor.prepare(spec);
}

void MySamplerVoice::updateGain(float newVal)
{
    mGain.setGainLinear(newVal);
}

void MySamplerVoice::updateFilter(float srate, float newMenu, float newFreq, float newRes, bool bypass)
{
    if (newMenu == 0){
        mFilter.parameters->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
    } else {
        mFilter.parameters->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
    }
    mFilter.parameters->setCutOffFrequency(srate, newFreq, newRes);
    filterNotBypassed = bypass;
}

void MySamplerVoice::updateCompressorThresh(float thresh)
{
    mCompressor.setThreshold(thresh);
}

void MySamplerVoice::updateCompressorRatio(float ratio)
{
    mCompressor.setRatio(ratio);
}

void MySamplerVoice::updateCompressorAttack(float attack)
{
    mCompressor.setAttack(attack);
}

void MySamplerVoice::updateCompressorRelease(float release)
{
    mCompressor.setRelease(release);
}

void MySamplerVoice::updateCompressorGain(float gain)
{
    compGain.setGainLinear(gain);
}

void MySamplerVoice::updateCompressorBypass(bool bypass)
{
    compNotBypassed = bypass;
}

void MySamplerVoice::updateDistDrive(float newDrive)
{
    dist.updateDrive(newDrive);
}

void MySamplerVoice::updateDistRange(float newRange)
{
    dist.updateRange(newRange);
}

void MySamplerVoice::updateDistBlend(float newBlend)
{
    dist.updateBlend(newBlend);
}

void MySamplerVoice::updateDistGain(float newGain)
{
    dist.updateGain(newGain);
}

void MySamplerVoice::updateDistBypass(bool bypass)
{
    distNotBypassed = bypass;
}
