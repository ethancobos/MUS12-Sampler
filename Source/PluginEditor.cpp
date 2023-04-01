/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MUS_12_SamplerAudioProcessorEditor::MUS_12_SamplerAudioProcessorEditor (MUS_12_SamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    startTimerHz(30);
    setSize (800, 400);
}

MUS_12_SamplerAudioProcessorEditor::~MUS_12_SamplerAudioProcessorEditor()
{
    stopTimer();
}

//==============================================================================
void MUS_12_SamplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
    g.setColour(juce::Colours::white);
    
    juce::Rectangle<int> thumbnailBounds (10, 100, getWidth() - 20, getHeight() - 120);

    if (audioProcessor.getNumSamplerSounds() > 0){
        paintIfFileLoaded (g, thumbnailBounds);
    } else{
        paintIfNoFileLoaded (g, thumbnailBounds);
    }
}

void MUS_12_SamplerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
}

bool MUS_12_SamplerAudioProcessorEditor::isInterestedInFileDrag(const juce::StringArray& files)
{
    for(auto file : files){
        if(file.contains(".wav") || file.contains(".mp3") || file.contains(".aif")){
            return true;
        }
    }
    
    return false;
}

void MUS_12_SamplerAudioProcessorEditor::filesDropped(const juce::StringArray& files, int x, int y)
{
    for(auto file : files){
        if(isInterestedInFileDrag(file)){
            audioProcessor.loadFile(file);
        }
    }
    repaint();
}

void MUS_12_SamplerAudioProcessorEditor::paintIfNoFileLoaded(juce::Graphics& g, const juce::Rectangle<int>& thumbnailBounds)
{
    g.setColour (juce::Colours::darkgrey);
    g.fillRect (thumbnailBounds);
    g.setColour (juce::Colours::white);
    g.drawFittedText ("No File Loaded", thumbnailBounds, juce::Justification::centred, 1);
}

void MUS_12_SamplerAudioProcessorEditor::paintIfFileLoaded (juce::Graphics& g, const juce::Rectangle<int>& thumbnailBounds)
{
    g.setColour (juce::Colours::white);
    g.fillRect (thumbnailBounds);
    g.setColour (juce::Colours::red);
    
    juce::AudioThumbnail* thumbnail = audioProcessor.getThumbnail();
    auto audioLength = (float) thumbnail->getTotalLength();
    
    thumbnail->drawChannels(g, thumbnailBounds, 0.0, audioLength, 1.0f);
    
    auto playheadPos = juce::jmap<int>(audioProcessor.getSampleCount(),
                                       0,
                                       (int) thumbnail->getNumSamplesFinished(),
                                       thumbnailBounds.getX(),
                                       thumbnailBounds.getRight());

    g.setColour (juce::Colours::green);
    g.drawLine (playheadPos, thumbnailBounds.getY(), playheadPos, thumbnailBounds.getBottom(), 2.0f);

//    g.setColour(juce::Colours::black.withAlpha(0.2f));
//    g.fillRect(thumbnailBounds.getX(), thumbnailBounds.getY(), playheadPos, thumbnailBounds.getHeight());
}

void MUS_12_SamplerAudioProcessorEditor::timerCallback()
{
    repaint();
}

