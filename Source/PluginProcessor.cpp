/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MySamplerVoice.h"

//==============================================================================
MUS_12_SamplerAudioProcessor::MUS_12_SamplerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), mAPVTS(*this, nullptr, "PARAMETERS", createParameters())
#endif
{
    mFormatManager.registerBasicFormats();
    mAPVTS.state.addListener(this);
    
    for (int i = 0; i < mNumVoices; i++){
        mSampler.addVoice(new MySamplerVoice());
    }
    
}

MUS_12_SamplerAudioProcessor::~MUS_12_SamplerAudioProcessor()
{
    if(mFormatReader != nullptr){
        delete mFormatReader;
    }
}

//==============================================================================
const juce::String MUS_12_SamplerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MUS_12_SamplerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MUS_12_SamplerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MUS_12_SamplerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MUS_12_SamplerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MUS_12_SamplerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MUS_12_SamplerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MUS_12_SamplerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MUS_12_SamplerAudioProcessor::getProgramName (int index)
{
    return {};
}

void MUS_12_SamplerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MUS_12_SamplerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    mSampler.setCurrentPlaybackSampleRate(sampleRate);
    
    for (int i = 0; i < mSampler.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<MySamplerVoice*>(mSampler.getVoice(i))){
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }


}

void MUS_12_SamplerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MUS_12_SamplerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MUS_12_SamplerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i){
        buffer.clear (i, 0, buffer.getNumSamples());
    }
    
    for (const juce::MidiMessageMetadata m : midiMessages)
    {
        juce::MidiMessage message = m.getMessage();
        
        if (message.isNoteOn()) {
            // start increasing sample counter
            mIsNotePlayed = true;
        } else if (message.isNoteOff()) {
            // reset sample counter
            mIsNotePlayed = false;
        }
    }

    mSampleCount = mIsNotePlayed ? mSampleCount += buffer.getNumSamples() : 0;
    
    if (mIsNotePlayed){
        if(mSampleCount <= mNumSamplesInWF){
            mReducedSampleCount += buffer.getNumSamples();
        } else{
            mReducedSampleCount = mNumSamplesInWF;
        }
    } else{
        mReducedSampleCount = 0;
    }
    
    mSampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool MUS_12_SamplerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MUS_12_SamplerAudioProcessor::createEditor()
{
    return new MUS_12_SamplerAudioProcessorEditor (*this);
}

//==============================================================================
void MUS_12_SamplerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MUS_12_SamplerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//========================== My Functions ======================================


// function to get the file to be sampled through drag and drop
void MUS_12_SamplerAudioProcessor::loadFile(const juce::String& path)
{
    mSampler.clearSounds();
    auto file = juce::File(path);
    juce::AudioFormatReader* temp = mFormatReader;
    mFormatReader = mFormatManager.createReaderFor(file);
    if(temp != nullptr){
        delete temp;
    }
    
    // range of midi notes that can be played
    juce::BigInteger range;
    range.setRange(0, 128, true);
    
    // parameters in order: name, format reader, range of midi notes, base note (C3 or midi note 60),
    // attack and delay, sample length
    MySamplerSound* sampledFile = new MySamplerSound("Sample", *mFormatReader, range, 60, 0.0, 0.1, sampleTime);
    mNumSamplesInWF = sampledFile->getAudioData()->getNumSamples();
    mSampler.addSound(sampledFile);
}

juce::AudioProcessorValueTreeState::ParameterLayout MUS_12_SamplerAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;
    
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("AMPATTACK", "Attack", 0.0f, 5.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("AMPDECAY", "Decay", 0.0f, 3.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("AMPSUSTAIN", "Sustain", 0.0f, 1.0f, 1.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("AMPRELEASE", "Release", 0.0f, 5.0f, 0.0f));
    
    return { parameters.begin(), parameters.end() };
}

void MUS_12_SamplerAudioProcessor::valueTreePropertyChanged (juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
{

}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MUS_12_SamplerAudioProcessor();
}
