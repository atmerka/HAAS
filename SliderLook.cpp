/*
  ==============================================================================

    SliderLook.cpp
    Created: 4 Oct 2021 5:39:11pm
    Author:  trissy the sissy

  ==============================================================================
*/

#include "SliderLook.h"

void SliderLook::drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle s  ,Slider &slider)
{
    //draw outline
    g.setColour(Colours::black.withAlpha(0.5f));
    g.drawRect(x, y, width, height);
    
    //draw level of slider
    g.setColour(Colours::lightblue.withAlpha(0.4f));
    g.drawRect(x+1, y+1,int(sliderPos-12)-1 , height-2);
    
    g.setColour(juce::Colours::lightblue.withAlpha(0.2f));
    g.fillRect(x+1, y+1,int(sliderPos-12)-1 , height-2);
    
    
}
