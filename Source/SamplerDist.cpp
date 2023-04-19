/*
  ==============================================================================

    SamplerDist.cpp
    Created: 18 Apr 2023 6:00:45pm
    Author:  Ethan Cobos

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SamplerDist.h"

//==============================================================================
SamplerDist::SamplerDist(MUS_12_SamplerAudioProcessor& p) : audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

SamplerDist::~SamplerDist()
{
}

void SamplerDist::paint (juce::Graphics& g)
{
    float yStart = (getHeight() / 5) + 5.0f;
    
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::buttonMouseOverBackgroundColourId));
    g.fillRoundedRectangle(10.0f, 5.0f, getWidth() - 15.0f, getHeight() - 15.0f, 10.0f);
    g.setColour(getLookAndFeel().findColour(juce::Toolbar::separatorColourId));
    g.fillRoundedRectangle(15.0f, yStart, getWidth() - 25.0f, getHeight() - yStart - 15.0f, 10.0f);
}

void SamplerDist::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
