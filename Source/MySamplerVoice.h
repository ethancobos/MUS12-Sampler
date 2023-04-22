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
#include "MyDistortion.h"

using namespace juce;

class MySamplerSound : public SynthesiserSound
{
public:
    MySamplerSound (const String& name,
                    AudioFormatReader& source,
                    const BigInteger& midiNotes,
                    int midiNoteForNormalPitch,
                    double attackTimeSecs,
                    double releaseTimeSecs,
                    double maxSampleLengthSeconds);
    
    
    ~MySamplerSound() override;
    
    const String& getName() const noexcept                  { return name; }
    AudioBuffer<float>* getAudioData() const noexcept       { return data.get(); }
    void setEnvelopeParameters (ADSR::Parameters parametersToUse)    { params = parametersToUse; }
    
    //==============================================================================
    bool appliesToNote (int midiNoteNumber) override;
    bool appliesToChannel (int midiChannel) override;
    
private:
    //==============================================================================
    friend class MySamplerVoice;
    
    String name;
    std::unique_ptr<AudioBuffer<float>> data;
    double sourceSampleRate;
    BigInteger midiNotes;
    int length = 0, midiRootNote = 0;
    
    ADSR::Parameters params;
    
    JUCE_LEAK_DETECTOR (MySamplerSound)
};


//==============================================================================
/**
 A subclass of SynthesiserVoice that can play a SamplerSound.
 To use it, create a Synthesiser, add some SamplerVoice objects to it, then
 give it some SampledSound objects to play.
 @see SamplerSound, Synthesiser, SynthesiserVoice
 @tags{Audio}
 */
class MySamplerVoice : public SynthesiserVoice
{
public:
    //==============================================================================
    /** Creates a SamplerVoice. */
    MySamplerVoice();
    
    /** Destructor. */
    ~MySamplerVoice() override;
    
    //==============================================================================
    bool canPlaySound (SynthesiserSound*) override;
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound*, int pitchWheel) override;
    void stopNote (float velocity, bool allowTailOff) override;
    
    void pitchWheelMoved (int newValue) override;
    void controllerMoved (int controllerNumber, int newValue) override;
    void renderNextBlock (AudioBuffer<float>&, int startSample, int numSamples) override;
    using SynthesiserVoice::renderNextBlock;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void reset();
    void updateGain(float newVal);
    void updateFilter(float srate, float newMenu, float newFreq, float newRes, bool bypass);
    
    // compressor
    void updateCompressorThresh(float thresh);
    void updateCompressorRatio(float ratio);
    void updateCompressorAttack(float attack);
    void updateCompressorRelease(float release);
    void updateCompressorGain(float gain);
    void updateCompressorBypass(bool bypass);
    
    void updateDistDrive(float newDrive);
    void updateDistRange(float newRange);
    void updateDistBlend(float newBlend);
    void updateDistGain(float newGain);
    void updateDistBypass(bool bypass);
    
private:
    //==============================================================================
    double pitchRatio = 0;
    double sourceSamplePosition = 0;
    float lgain = 0, rgain = 0;
    
    dsp::Gain<float> mGain;
    dsp::StateVariableFilter::Filter<float> mFilter;
    bool filterNotBypassed;
    bool compNotBypassed;
    bool distNotBypassed;
    dsp::Compressor<float> mCompressor;
    dsp::Gain<float> compGain;
    MyDistortion dist;
    
    ADSR adsr;
    
    
    JUCE_LEAK_DETECTOR (MySamplerVoice)
};
