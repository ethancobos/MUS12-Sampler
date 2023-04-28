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
            audioProcessor.getAPVTS().state.setProperty(audioProcessor.fileForWave, juce::var(file), nullptr);
            fileLoaded = true;
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
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::buttonMouseOverBackgroundColourId));
    g.fillRoundedRectangle(5.0f, 5.0f, getWidth() - 10.0f, getHeight() - 10.0f, 10.0f);
    if (audioProcessor.getNumSamplerSounds() > 0){
        if(!fileLoaded){
            auto filePath = audioProcessor.getAPVTS().state.getProperty(audioProcessor.fileForWave).toString();
            setThumbnail(filePath);
            fileLoaded = true;
        }
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
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::labelTextColourId));
    g.fillRoundedRectangle(10.0f, 10.0f, getWidth() - 20.0f, getHeight() - 20.0f, 10.0f);
    g.setColour (juce::Colours::black);
    g.drawText ("Drag File To Load", getLocalBounds(), juce::Justification::centred, true);
}

void WaveFormThumbnail::paintIfFileLoaded (juce::Graphics& g)
{
    float newHeight = getHeight() - 20.0f;
    float newWidth = getWidth() - 20.0f;
    float newX = 10.0f;
    float newY = 10.0f;
    
    juce::Rectangle<int> waveBounds = juce::Rectangle<int>(newX, newY, newWidth, newHeight);
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::labelTextColourId));
    g.fillRect(waveBounds);
    g.setColour(getLookAndFeel().findColour(juce::TextButton::buttonOnColourId));
    
    int sTime = audioProcessor.getSampleTime();
    float totAudioLen = (float) thumbnail.getTotalLength();
    float audioLength = totAudioLen < sTime ? totAudioLen : sTime;
    
    thumbnail.drawChannels(g, waveBounds, 0.0, audioLength, 1.0f);
    
    auto playheadPos = juce::jmap<int>(audioProcessor.getSampleCount(),
                                       0,
                                       audioProcessor.getNumSIWF(),
                                       0,
                                       newWidth);

    g.setColour (getLookAndFeel().findColour(juce::Toolbar::separatorColourId));
    g.drawLine (playheadPos + newX, newY, playheadPos + newX, newHeight + 10.0f, 2.0f);
    g.setColour(juce::Colours::black.withAlpha(0.2f));
    g.fillRect(newX, newY, float(playheadPos), newHeight);
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::buttonMouseOverBackgroundColourId));
    g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(7.5), 10.0f, 5.0f);
}
