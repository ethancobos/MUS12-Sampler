/*
  ==============================================================================

    AmplitudeEnvelope.h
    Created: 9 Apr 2023 5:43:18pm
    Author:  Ethan Cobos

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class AmplitudeEnvelope  : public juce::Component
{
public:
    AmplitudeEnvelope(MUS_12_SamplerAudioProcessor& p);
    ~AmplitudeEnvelope() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    MUS_12_SamplerAudioProcessor& audioProcessor;
    
    juce::Slider mAttackS, mDecayS, mSustainS, mReleaseS;
    juce::Label mAttackL, mDecayL, mSustainL, mReleaseL;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mAttackAtach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mDecayAtach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mSustainAtach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mReleaseAtach;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmplitudeEnvelope)
};
