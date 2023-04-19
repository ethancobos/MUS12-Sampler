/*
  ==============================================================================

    SamplerDist.h
    Created: 18 Apr 2023 6:00:45pm
    Author:  Ethan Cobos

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class SamplerDist  : public juce::Component
{
public:
    SamplerDist(MUS_12_SamplerAudioProcessor& p);
    ~SamplerDist() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    MUS_12_SamplerAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerDist)
};
