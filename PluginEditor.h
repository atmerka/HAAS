/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SliderLook.h"


//==============================================================================
/**
*/
class HaastAlphestaelAudioProcessorEditor  : public AudioProcessorEditor//, public Slider::Listener
{
public:
    HaastAlphestaelAudioProcessorEditor (HaastAlphestaelAudioProcessor&);
    ~HaastAlphestaelAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    
private:
//    void sliderValueChanged(Slider* slider) override;
    
    //Look and feel
    SliderLook sexyLook;
    
    //Sliders
    Slider delayAmt;
    Slider delayAmt2;
    
    HaastAlphestaelAudioProcessor& processor;
    
public:
    
    //for parameters (value tree)
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> haastSliderAttachment;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> haastSliderAttachment2;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HaastAlphestaelAudioProcessorEditor)
};
