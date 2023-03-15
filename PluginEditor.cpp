/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HaastAlphestaelAudioProcessorEditor::HaastAlphestaelAudioProcessorEditor (HaastAlphestaelAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // window size
    setSize (500   , 200);
 
    //make sliders visible to parent
    addAndMakeVisible(delayAmt);
    addAndMakeVisible(delayAmt2);
    
    
    //set values and textbox of sliders
    delayAmt.setRange(0.0000f, 0.1000f, 0.00001f);
    delayAmt.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

//    delayAmt.setSkewFactor(4);
//    delayAmt.addListener(this);
//    delayAmt.setValue(processor.delayAmount);
//    delayAmt.setValue(0);
    
    delayAmt2.setRange(0.0000f, 0.1000f, 0.00001f);
    delayAmt2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);


    //set style and look of sliders
    delayAmt.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    delayAmt.setLookAndFeel(&sexyLook);
    
    delayAmt2.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    delayAmt2.setLookAndFeel(&sexyLook);

    
    //attach valuetree (for parameters)
    haastSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.treeState, "DELAY", delayAmt);
    haastSliderAttachment2 = std::make_unique<AudioProcessorValueTreeState::SliderAttachment> (processor.treeState, "DELAY2", delayAmt2);

}

HaastAlphestaelAudioProcessorEditor::~HaastAlphestaelAudioProcessorEditor()
{
}

//==============================================================================
void HaastAlphestaelAudioProcessorEditor::paint (Graphics& g)
{
    //fill background
    g.fillAll (Colours::lightgrey.withAlpha(0.6f) );
    
    //Draw Title
    g.setColour(Colours::darkslategrey.withAlpha(0.6f));
    g.setFont(30.0f);
    g.drawText("H  A  A  S", 0, 0, getWidth(), getHeight()*0.33 , Justification::centred);
    
    
    //Write the delay amount on top of each slider
    g.setFont(14.0f);
    g.setColour(Colours::lightblue);
    g.drawText("LEFT CHANNEL DELAY = " + String(processor.delayAmount) + " " + String(std::ceil(100*processor.delayAmount/processor.currentSampleRate*100)/100)
               + " ms", 0, getHeight()*1/3, getWidth(), getHeight()*0.33   , Justification::centred);
    
    g.drawText("RIGHT CHANNEL DELAY = " +String(processor.delayAmount2)  + " " + String(std::ceil(100*processor.delayAmount2/processor.currentSampleRate*100)/100)
                  + " ms", 0, getHeight()*2/3, getWidth(), getHeight()*0.33   , Justification::centred);
    
}

void HaastAlphestaelAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    delayAmt.setBounds(0, getHeight()*1/3, getWidth(), getHeight()*0.33);
    delayAmt2.setBounds(0, getHeight()*2/3, getWidth(), getHeight()*0.33);
    
    
    
    repaint();
    
}

//void HaastAlphestaelAudioProcessorEditor::sliderValueChanged(Slider* slider)
//{
 //   processor.delayAmount = processor.getSampleRate()*delayAmt.getValue();
//}
