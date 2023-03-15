/*
  ==============================================================================

    SliderLook.h
    Created: 4 Oct 2021 5:39:11pm
    Author:  trissy the sissy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class SliderLook : public LookAndFeel_V4
{
public:
    
    void drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle s  ,Slider &slider) override;
    
    
};

