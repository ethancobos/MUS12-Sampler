/*
  ==============================================================================

    customSamplerSound.h
    Created: 13 Apr 2023 11:14:03am
    Author:  Ethan Cobos

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class customSamplerSound : public juce::SamplerSound
{
public:
    bool appliesToNote (int midiNoteNumber) override { return true; }
    bool appliesToChannel (int midiChannel) override { return true; }
};
