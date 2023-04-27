/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MySamplerVoice.h"

//==============================================================================

// ampenv idents
const juce::String MUS_12_SamplerAudioProcessor::ampAttack = "AMPATTACK";
const juce::String MUS_12_SamplerAudioProcessor::ampDecay = "AMPDECAY";
const juce::String MUS_12_SamplerAudioProcessor::ampSustain = "AMPSUSTAIN";
const juce::String MUS_12_SamplerAudioProcessor::ampRelease = "AMPRELEASE";

// filter idents
const juce::String MUS_12_SamplerAudioProcessor::filterFreq = "FILTERFREQ";
const juce::String MUS_12_SamplerAudioProcessor::filterRes = "FILTERRES";
const juce::String MUS_12_SamplerAudioProcessor::filterCoice = "FILTERCHOSE";
const juce::String MUS_12_SamplerAudioProcessor::filterBypass = "FILTERBYPASS";
const juce::String MUS_12_SamplerAudioProcessor::filterGain = "FILTERGAIN";

// main gain
const juce::String MUS_12_SamplerAudioProcessor::outputGain = "OUTGAIN";

// compression
const juce::String MUS_12_SamplerAudioProcessor::compAttack = "COMPATT";
const juce::String MUS_12_SamplerAudioProcessor::compRelease = "COMPREL";
const juce::String MUS_12_SamplerAudioProcessor::compThresh = "COMPTHRESH";
const juce::String MUS_12_SamplerAudioProcessor::compRatio = "COMPRATIO";
const juce::String MUS_12_SamplerAudioProcessor::compGain = "COMPGAIN";
const juce::String MUS_12_SamplerAudioProcessor::compBypass = "COMPBYPASS";

// distortion
const juce::String MUS_12_SamplerAudioProcessor::distDrive = "DISTDRIVE";
const juce::String MUS_12_SamplerAudioProcessor::distRange = "DISTRANGE";
const juce::String MUS_12_SamplerAudioProcessor::distBlend = "DISTBLEND";
const juce::String MUS_12_SamplerAudioProcessor::distGain = "DISTGAIN";
const juce::String MUS_12_SamplerAudioProcessor::distBypass = "DISTBYPASS";

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
    
    for (int i = 0; i < mNumVoices; i++){
        mSampler.addVoice(new MySamplerVoice());
    }
    
    mAPVTS.addParameterListener(compThresh, this);
    mAPVTS.addParameterListener(compRatio, this);
    mAPVTS.addParameterListener(compAttack, this);
    mAPVTS.addParameterListener(compRelease, this);
    mAPVTS.addParameterListener(compGain, this);
    mAPVTS.addParameterListener(compBypass, this);
    mAPVTS.addParameterListener(distDrive, this);
    mAPVTS.addParameterListener(distRange, this);
    mAPVTS.addParameterListener(distGain, this);
    mAPVTS.addParameterListener(distBlend, this);
    mAPVTS.addParameterListener(distBypass, this);
    mAPVTS.addParameterListener(filterCoice, this);
    mAPVTS.addParameterListener(filterFreq, this);
    mAPVTS.addParameterListener(filterRes, this);
    mAPVTS.addParameterListener(filterBypass, this);
    mAPVTS.addParameterListener(filterGain, this);
    mAPVTS.addParameterListener(outputGain, this);
    mAPVTS.addParameterListener(ampAttack, this);
    mAPVTS.addParameterListener(ampDecay, this);
    mAPVTS.addParameterListener(ampSustain, this);
    mAPVTS.addParameterListener(ampRelease, this);
    
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
    lastSampleRate = sampleRate;
    
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
            noteHzm = message.getMidiNoteInHertz(message.getNoteNumber()) / 261.625565;
        } else if (message.isNoteOff()) {
            // reset sample counter
            mIsNotePlayed = false;
        }
    }

    mSampleCount = mIsNotePlayed ? mSampleCount += (buffer.getNumSamples()  * noteHzm) : 0;
    
    if(mSampleCount > mNumSamplesInWF){
        mSampleCount = mNumSamplesInWF;
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
    auto state = mAPVTS.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void MUS_12_SamplerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (mAPVTS.state.getType()))
            mAPVTS.replaceState (juce::ValueTree::fromXml (*xmlState));
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
    updateAmpEnvelope();
    updateGain();
    updateFilterBypass();
    updateFilterFreq();
    updateFilterRes();
    updateFilterMenu();
    updateFilterGain();
    updateCompressorThresh();
    updateCompressorRatio();
    updateCompressorAttack();
    updateCompressorRelease();
    updateCompressorGain();
    updateCompressorBypass();
    updateDistortionDrive();
    updateDistortionRange();
    updateDistortionBlend();
    updateDistortionGain();
    updateDistortionBypass();
}

void MUS_12_SamplerAudioProcessor::updateAmpEnvelope()
{
    mAmpParams.attack = mAPVTS.getRawParameterValue(ampAttack)->load();
    mAmpParams.decay = mAPVTS.getRawParameterValue(ampDecay)->load();
    mAmpParams.sustain = mAPVTS.getRawParameterValue(ampSustain)->load();
    mAmpParams.release = mAPVTS.getRawParameterValue(ampRelease)->load();
    
    for(int i = 0; i < mSampler.getNumSounds(); i++){
        if(auto sound = dynamic_cast<MySamplerSound*>(mSampler.getSound(i).get())){
            sound->setEnvelopeParameters(mAmpParams);
        }
    }
}

void MUS_12_SamplerAudioProcessor::updateGain()
{
    float newGain = mAPVTS.getRawParameterValue(outputGain)->load();

    for (int i = 0; i < mSampler.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<MySamplerVoice*>(mSampler.getVoice(i))){
            voice->updateGain(newGain);
        }
    }
}

void MUS_12_SamplerAudioProcessor::updateFilterMenu()
{
    float menu = mAPVTS.getRawParameterValue(filterCoice)->load();
    
    for (int i = 0; i < mSampler.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<MySamplerVoice*>(mSampler.getVoice(i))){
            voice->updateFilterMenu(menu);
        }
    }
}

void MUS_12_SamplerAudioProcessor::updateFilterFreq()
{
    float freq = mAPVTS.getRawParameterValue(filterFreq)->load();
    
    for (int i = 0; i < mSampler.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<MySamplerVoice*>(mSampler.getVoice(i))){
            voice->updateFilterFreq(freq);
        }
    }
}

void MUS_12_SamplerAudioProcessor::updateFilterRes()
{
    float res = mAPVTS.getRawParameterValue(filterRes)->load();
    
    for (int i = 0; i < mSampler.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<MySamplerVoice*>(mSampler.getVoice(i))){
            voice->updateFilterRes(res);
        }
    }
}

void MUS_12_SamplerAudioProcessor::updateFilterBypass()
{
    bool bypass = mAPVTS.getRawParameterValue(filterBypass)->load();
    
    for (int i = 0; i < mSampler.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<MySamplerVoice*>(mSampler.getVoice(i))){
            voice->updateFilterBypass(bypass);
        }
    }
}

void MUS_12_SamplerAudioProcessor::updateFilterGain()
{
    float gain = mAPVTS.getRawParameterValue(filterGain)->load();
    
    for (int i = 0; i < mSampler.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<MySamplerVoice*>(mSampler.getVoice(i))){
            voice->updateFilterGain(gain);
        }
    }
}

//========================== Compression ======================================

void MUS_12_SamplerAudioProcessor::updateCompressorThresh()
{
    float thresh = mAPVTS.getRawParameterValue(compThresh)->load();
    
    for (int i = 0; i < mSampler.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<MySamplerVoice*>(mSampler.getVoice(i))){
            voice->updateCompressorThresh(thresh);
        }
    }
}

void MUS_12_SamplerAudioProcessor::updateCompressorRatio()
{
    float ratio = mAPVTS.getRawParameterValue(compRatio)->load();
    
    for (int i = 0; i < mSampler.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<MySamplerVoice*>(mSampler.getVoice(i))){
            voice->updateCompressorRatio(ratio);
        }
    }
}

void MUS_12_SamplerAudioProcessor::updateCompressorAttack()
{
    float attack = mAPVTS.getRawParameterValue(compAttack)->load();
    
    for (int i = 0; i < mSampler.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<MySamplerVoice*>(mSampler.getVoice(i))){
            voice->updateCompressorAttack(attack);
        }
    }
}

void MUS_12_SamplerAudioProcessor::updateCompressorRelease()
{
    float release = mAPVTS.getRawParameterValue(compRelease)->load();
    
    for (int i = 0; i < mSampler.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<MySamplerVoice*>(mSampler.getVoice(i))){
            voice->updateCompressorRelease(release);
        }
    }
}

void MUS_12_SamplerAudioProcessor::updateCompressorGain()
{
    float gain = mAPVTS.getRawParameterValue(compGain)->load();
    
    for (int i = 0; i < mSampler.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<MySamplerVoice*>(mSampler.getVoice(i))){
            voice->updateCompressorGain(gain);
        }
    }
}

void MUS_12_SamplerAudioProcessor::updateCompressorBypass()
{
    bool bypass = mAPVTS.getRawParameterValue(compBypass)->load();
    
    for (int i = 0; i < mSampler.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<MySamplerVoice*>(mSampler.getVoice(i))){
            voice->updateCompressorBypass(bypass);
        }
    }
}

//========================== Distortion =====================================

void MUS_12_SamplerAudioProcessor::updateDistortionDrive()
{
    float drive = mAPVTS.getRawParameterValue(distDrive)->load();
    
    for (int i = 0; i < mSampler.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<MySamplerVoice*>(mSampler.getVoice(i))){
            voice->updateDistDrive(drive);
        }
    }
}

void MUS_12_SamplerAudioProcessor::updateDistortionRange()
{
    float range = mAPVTS.getRawParameterValue(distRange)->load();
    
    for (int i = 0; i < mSampler.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<MySamplerVoice*>(mSampler.getVoice(i))){
            voice->updateDistRange(range);
        }
    }
}

void MUS_12_SamplerAudioProcessor::updateDistortionBlend()
{
    float blend = mAPVTS.getRawParameterValue(distBlend)->load();
    
    for (int i = 0; i < mSampler.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<MySamplerVoice*>(mSampler.getVoice(i))){
            voice->updateDistBlend(blend);
        }
    }
}

void MUS_12_SamplerAudioProcessor::updateDistortionGain()
{
    float gain = mAPVTS.getRawParameterValue(distGain)->load();
    
    for (int i = 0; i < mSampler.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<MySamplerVoice*>(mSampler.getVoice(i))){
            voice->updateDistGain(gain);
        }
    }
}

void MUS_12_SamplerAudioProcessor::updateDistortionBypass()
{
    bool bypass = mAPVTS.getRawParameterValue(distBypass)->load();
    
    for (int i = 0; i < mSampler.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<MySamplerVoice*>(mSampler.getVoice(i))){
            voice->updateDistBypass(bypass);
        }
    }
}

//========================== ValueTree ======================================

void MUS_12_SamplerAudioProcessor::parameterChanged (const String &parameterID, float newValue)
{
    if (parameterID == compThresh){
        updateCompressorThresh();
    } else if (parameterID == compRatio){
        updateCompressorRatio();
    } else if (parameterID == compAttack){
        updateCompressorAttack();
    } else if (parameterID == compRelease){
        updateCompressorRelease();
    } else if (parameterID == compGain){
        updateCompressorGain();
    } else if (parameterID == compBypass){
        updateCompressorBypass();
    } else if (parameterID == distDrive){
        updateDistortionDrive();
    } else if (parameterID == distRange){
        updateDistortionRange();
    } else if (parameterID == distBlend){
        updateDistortionBlend();
    } else if (parameterID == distGain){
        updateDistortionGain();
    } else if (parameterID == distBypass){
        updateDistortionBypass();
    } else if (parameterID == filterFreq){
        updateFilterFreq();
    } else if (parameterID == filterCoice){
        updateFilterMenu();
    } else if (parameterID == filterRes){
        updateFilterRes();
    } else if (parameterID == filterBypass){
        updateFilterBypass();
    } else if (parameterID == filterGain){
        updateFilterGain();
    } else if (parameterID == outputGain){
        updateGain();
    } else {
        updateAmpEnvelope();
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout MUS_12_SamplerAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;
    juce::StringArray filters = {"HP", "LP"};
    
    // Amp env
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(ampAttack, "Attack", 0.0f, 5.0f, 0.1f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(ampDecay, "Decay", 0.0f, 3.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(ampSustain, "Sustain", 0.0f, 1.0f, 1.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(ampRelease, "Release", 0.0f, 5.0f, 0.1f));
    
    // filter stuff
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(filterFreq, "Frequency", 20.0f, 20000.0f, 1000.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(filterRes, "Q", 1.0f, 5.0f, 2.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>(filterCoice, "filters", filters, 0));
    parameters.push_back(std::make_unique<juce::AudioParameterBool>(filterBypass, "filterBypass", false));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(filterGain, "filter gain", 0.0f, 2.0f, 1.0f));
    
    // output gain
    parameters.push_back (std::make_unique<juce::AudioParameterFloat>(outputGain, "Gain", 0.0f, 2.0f, 1.0f));
    
    // compressor
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(compAttack, "comp attack", 0.0f, 200.0f, 10.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(compRelease, "comp release", 0.0f, 200.0f, 10.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(compRatio, "comp ratio", 1.0f, 5.0f, 2.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(compThresh, "comp thresh", -40.0f, 0.0f, -10.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(compGain, "comp gain", 0.0f, 2.0f, 1.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterBool>(compBypass, "compBypass", false));
    
    // Distotion
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(distDrive, "dist drive", 0.0f, 1.0f, 0.01f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(distRange, "dist range", 0.0f, 3000.0f, 1000.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(distBlend, "dist blend", 0.0f, 1.0f, 0.5f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(distGain, "dist gain", 0.0f, 2.0f, 1.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterBool>(distBypass, "compBypass", false));
    
    return { parameters.begin(), parameters.end() };
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MUS_12_SamplerAudioProcessor();
}
