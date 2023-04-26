/*
  ==============================================================================

    SamplerCompresh.h
    Created: 17 Apr 2023 12:21:59pm
    Author:  Ethan Cobos

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class SamplerCompresh  : public juce::Component
{
public:
    SamplerCompresh(MUS_12_SamplerAudioProcessor& p);
    ~SamplerCompresh() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    MUS_12_SamplerAudioProcessor& audioProcessor;
    
    juce::Slider attackS, releaseS, threshS, ratioS, gainS;
    juce::Label attackL, releaseL, threshL, ratioL;
    juce::ToggleButton compBypass;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAtach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAtach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> threshAtach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ratioAtach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAtach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAtach;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerCompresh)
};
