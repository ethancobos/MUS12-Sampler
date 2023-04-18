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
                                      public juce::ValueTree::Listener
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    
    static const juce::String filterFreq;
    static const juce::String filterRes;
    static const juce::String filterCoice;
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
    std::atomic<int>& getReducedSC() { return mReducedSampleCount; };
    int getSampleTime() { return sampleTime; };
    int getNumSIWF() { return mNumSamplesInWF; };
    juce::AudioProcessorValueTreeState& getAPVTS(){ return mAPVTS; };
    void updateAmpEnvelope();
    void updateGain();
    void updateFilter();
    void updateCompressor();

private:
    
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
    std::atomic<int> mReducedSampleCount { 0 };
    
    juce::AudioProcessorValueTreeState mAPVTS;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    
    juce::ADSR::Parameters mAmpParams;
    void valueTreePropertyChanged (juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property) override;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MUS_12_SamplerAudioProcessor)
};
