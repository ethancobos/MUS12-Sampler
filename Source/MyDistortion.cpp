/*
  ==============================================================================

    MyDistortion.cpp
    Created: 21 Apr 2023 5:18:35pm
    Author:  Ethan Cobos

  ==============================================================================
*/

#include "MyDistortion.h"
#include <cmath>


float MyDistortion::processSample(float sample)
{
    float clean_sample = sample;
    float modified_sample = sample;
    
    modified_sample *= drive * range;
    
    return ((M_2_PI * atan(modified_sample) * blend) + (clean_sample * (1 - blend))) * gain;
}

void MyDistortion::updateDrive(float newDrive)
{
    drive = newDrive;
}

void MyDistortion::updateRange(float newRange)
{
    range = newRange;
}

void MyDistortion::updateBlend(float newBlend)
{
    blend = newBlend;
}

void MyDistortion::updateGain(float newGain)
{
    gain = newGain;
}
