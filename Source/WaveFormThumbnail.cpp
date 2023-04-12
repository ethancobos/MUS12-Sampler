/*
  ==============================================================================

    WaveFormThumbnail.cpp
    Created: 2 Apr 2023 10:12:54am
    Author:  Ethan Cobos

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveFormThumbnail.h"

//==============================================================================
WaveFormThumbnail::WaveFormThumbnail(MUS_12_SamplerAudioProcessor& p) : audioProcessor(p),thumbnailCache (5),
    thumbnail (512, mFormatManager, thumbnailCache)
{
    // support for most audio file formats
    mFormatManager.registerBasicFormats();

}

WaveFormThumbnail::~WaveFormThumbnail()
{
}

bool WaveFormThumbnail::isInterestedInFileDrag(const juce::StringArray& files)
{
    for(auto file : files){
        if(file.contains(".wav") || file.contains(".mp3") || file.contains(".aif")){
            return true;
        }
    }
    
    return false;
}

void WaveFormThumbnail::filesDropped(const juce::StringArray& files, int x, int y)
{
    for(auto file : files){
        if(isInterestedInFileDrag(file)){
            audioProcessor.loadFile(file);
            setThumbnail(file);
        }
    }
    repaint();
}

void WaveFormThumbnail::setThumbnail(const juce::String& path)
{
    auto file = juce::File(path);
    thumbnail.setSource(new juce::FileInputSource(file));
}

void WaveFormThumbnail::paint (juce::Graphics& g)
{
    if (audioProcessor.getNumSamplerSounds() > 0){
        paintIfFileLoaded (g);
    } else{
        paintIfNoFileLoaded (g);
    }
}

void WaveFormThumbnail::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void WaveFormThumbnail::paintIfNoFileLoaded(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
    g.setColour (juce::Colours::white);
    g.drawText ("Drag File To Load", getLocalBounds(), juce::Justification::centred, true);
}

void WaveFormThumbnail::paintIfFileLoaded (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);
    g.setColour (juce::Colours::red);
    
    int sTime = audioProcessor.getSampleTime();
    float totAudioLen = (float) thumbnail.getTotalLength();
    float audioLength = totAudioLen < sTime ? totAudioLen : sTime;
    
    thumbnail.drawChannels(g, getLocalBounds(), 0.0, audioLength, 1.0f);
    
    auto playheadPos = juce::jmap<int>(audioProcessor.getReducedSC(),
                                       0,
                                       audioProcessor.getNumSIWF(),
                                       0,
                                       getWidth());

    g.setColour (juce::Colours::green);
    g.drawLine (playheadPos, 0, playheadPos, getHeight(), 2.0f);
    g.setColour(juce::Colours::black.withAlpha(0.2f));
    g.fillRect(0, 0, playheadPos, getHeight());
}
