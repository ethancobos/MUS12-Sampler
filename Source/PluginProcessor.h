/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class MUS_12_SamplerAudioProcessor  : public juce::AudioProcessor,
                                      public juce::AudioProcessorValueTreeState::Listener
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    
    static const juce::String filterFreq;
    static const juce::String filterRes;
    static const juce::String filterCoice;
    static const juce::String filterGain;
    static const juce::String filterBypass;
    static const juce::String ampAttack;
    static const juce::String ampDecay;
    static const juce::String ampSustain;
    static const juce::String ampRelease;
    static const juce::String outputGain;
    static const juce::String compAttack;
    static const juce::String compRelease;
    static const juce::String compThresh;
    static const juce::String compRatio;
    static const juce::String compGain;
    static const juce::String compBypass;
    static const juce::String distDrive;
    static const juce::String distRange;
    static const juce::String distBlend;
    static const juce::String distGain;
    static const juce::String distBypass;
    
    //==============================================================================
    MUS_12_SamplerAudioProcessor();
    ~MUS_12_SamplerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //========================== My Functions ======================================
    void loadFile(const juce::String& path);
    int getNumSamplerSounds() { return mSampler.getNumSounds(); };
    std::atomic<bool>& isNotePlayed() { return mIsNotePlayed; };
    std::atomic<int>& getSampleCount() { return mSampleCount; };
    int getSampleTime() { return sampleTime; };
    int getNumSIWF() { return mNumSamplesInWF; };
    juce::AudioProcessorValueTreeState& getAPVTS(){ return mAPVTS; };
    void updateAmpEnvelope();
    
    //========================== Distortion ======================================
    void updateDistortionDrive();
    void updateDistortionRange();
    void updateDistortionBlend();
    void updateDistortionGain();
    void updateDistortionBypass();
    
    //========================== Filter ======================================
    void updateFilterMenu();
    void updateFilterFreq();
    void updateFilterRes();
    void updateFilterBypass();
    void updateFilterGain();
    
    //========================== Compression ======================================
    void updateCompressorThresh();
    void updateCompressorRatio();
    void updateCompressorAttack();
    void updateCompressorRelease();
    void updateCompressorGain();
    void updateCompressorBypass();
    
    //========================== Gain ======================================
    void updateGain();
    
private:
    
    float lastSampleRate = 44100;
    
    // sampler
    juce::Synthesiser mSampler;
    
    // number of voices for the sampler
    const int mNumVoices { 5 };
    const int sampleTime { 10 };
    
    juce::AudioFormatManager mFormatManager;
    juce::AudioFormatReader* mFormatReader { nullptr };
    int mNumSamplesInWF = 0;
    
    std::atomic<bool> mIsNotePlayed { false };
    std::atomic<int> mSampleCount { 0 };
    std::atomic<float> noteHzm { 1 };
    
    juce::AudioProcessorValueTreeState mAPVTS;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    
    juce::ADSR::Parameters mAmpParams;
    void parameterChanged(const juce::String &parameterID, float newValue) override;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MUS_12_SamplerAudioProcessor)
};
