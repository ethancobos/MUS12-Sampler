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
    mLoadFileButton.onClick = [&](){ audioProcessor.loadFile(); };
    addAndMakeVisible(mLoadFileButton);
    
    setSize (200, 200);
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
    g.setFont(15.0f);
    
    if(audioProcessor.getNumSamplerSounds() > 0){
        g.fillAll (juce::Colours::blueviolet);
        
        g.drawText("Sound Loaded", getWidth() / 2 - 50, getHeight() / 2 - 10, 100, 20, juce::Justification::centred);
    } else {
        g.drawText("No Sound Loaded", getWidth() / 2 - 50, getHeight() / 2 - 10, 100, 20, juce::Justification::centred);
    }
}

void MUS_12_SamplerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
   // mLoadFileButton.setBounds(getWidth() / 2 - 50, getWidth() / 2 - 50, 100, 100);
    
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
