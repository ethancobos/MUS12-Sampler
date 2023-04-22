/*
  ==============================================================================

    MyDistortion.h
    Created: 21 Apr 2023 5:18:35pm
    Author:  Ethan Cobos

  ==============================================================================
*/

#pragma once


class MyDistortion {
    
public:
    float processSample(float sample);
    void updateDrive(float newDrive);
    void updateRange(float newRange);
    void updateBlend(float newBlend);
    void updateGain(float newGain);
    
private:
    float drive;
    float range;
    float blend;
    float gain;
};
