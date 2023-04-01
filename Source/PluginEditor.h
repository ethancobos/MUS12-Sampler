/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MUS_12_SamplerAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                            public juce::FileDragAndDropTarget
{
public:
    MUS_12_SamplerAudioProcessorEditor (MUS_12_SamplerAudioProcessor&);
    ~MUS_12_SamplerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;
    void paintIfNoFileLoaded (juce::Graphics& g, const juce::Rectangle<int>& thumbnailBounds);
    void paintIfFileLoaded (juce::Graphics& g, const juce::Rectangle<int>& thumbnailBounds);
    
    //========================== My Functions ======================================
    void drawWaveForm(juce::Graphics& g, const juce::Rectangle<int> & area);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    MUS_12_SamplerAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MUS_12_SamplerAudioProcessorEditor)
};
