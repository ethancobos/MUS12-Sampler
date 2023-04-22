/*
  ==============================================================================

    SamplerDistortion.h
    Created: 21 Apr 2023 5:18:11pm
    Author:  Ethan Cobos

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class SamplerDistortion  : public juce::Component
{ 
public:
    SamplerDistortion(MUS_12_SamplerAudioProcessor& p);
    ~SamplerDistortion() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    MUS_12_SamplerAudioProcessor& audioProcessor;
    
    juce::Slider driveS, rangeS, blendS, gainS;
    juce::Label driveL, rangeL, blendL, gainL;
    juce::ToggleButton distBypass;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAtach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rangeAtach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> blendAtach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAtach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAtach;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerDistortion)
};
