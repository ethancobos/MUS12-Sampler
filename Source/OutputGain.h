/*
  ==============================================================================

    OutputGain.h
    Created: 14 Apr 2023 5:00:45pm
    Author:  Ethan Cobos

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class OutputGain  : public juce::Component
{
public:
    OutputGain(MUS_12_SamplerAudioProcessor& p);
    ~OutputGain() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    MUS_12_SamplerAudioProcessor& audioProcessor;
    
    juce::Slider mGainS;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mGainAtach;
    
     
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OutputGain)
};
