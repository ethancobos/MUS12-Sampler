/*
  ==============================================================================

    WaveFormThumbnail.h
    Created: 2 Apr 2023 10:12:54am
    Author:  Ethan Cobos

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class WaveFormThumbnail  : public juce::Component,
                           public juce::FileDragAndDropTarget
{
public:
    WaveFormThumbnail(MUS_12_SamplerAudioProcessor& p);
    ~WaveFormThumbnail() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setThumbnail(const juce::String& path);
    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;

private:
    
    std::atomic<bool> fileLoaded { false };
    MUS_12_SamplerAudioProcessor& audioProcessor;
    juce::AudioFormatManager mFormatManager;
    juce::AudioThumbnailCache thumbnailCache;
    juce::AudioThumbnail thumbnail;
    
    void paintIfNoFileLoaded (juce::Graphics& g);
    void paintIfFileLoaded (juce::Graphics& g);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveFormThumbnail)
};
