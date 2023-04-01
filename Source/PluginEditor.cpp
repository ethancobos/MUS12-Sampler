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
    
    setSize (800, 400);
}

MUS_12_SamplerAudioProcessorEditor::~MUS_12_SamplerAudioProcessorEditor()
{
    
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

    audioProcessor.drawWaveForm(g, thumbnailBounds);
}
