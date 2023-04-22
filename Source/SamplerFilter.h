/*
  ==============================================================================
    SamplerFilter.h
    Created: 12 Apr 2023 3:26:29pm
    Author:  Ethan Cobos
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomGUI.h"

//==============================================================================
/*
*/
class SamplerFilter  : public juce::Component
{
public:
    SamplerFilter(MUS_12_SamplerAudioProcessor& p);
    ~SamplerFilter() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    MUS_12_SamplerAudioProcessor& audioProcessor;
    
    juce::ComboBox filterMenu;
    juce::Slider cutoffS, resonanceS, gainS;
    juce::ToggleButton filterBypass;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffAtach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> resonanceAtach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAtach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> menuAtach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAtach;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerFilter)
};
