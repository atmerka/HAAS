/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#define DELAY_ID "DELAY"
#define DELAY_NAME "Delay"

#define DELAY_ID2 "DELAY2"
#define DELAY_NAME2 "Delay2"

//==============================================================================
/**
*/
class HaastAlphestaelAudioProcessor  : public AudioProcessor, public ValueTree::Listener
{
public:
    //==============================================================================
    HaastAlphestaelAudioProcessor();
    ~HaastAlphestaelAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void pushNextSampleIntoFifoL(float sample) noexcept;
    void pushNextSampleIntoFifoR(float sample) noexcept;
    
    
    //For HAAS======================================================================================
    //buffer count
    int indexWeAreAddingToR = 30;
    int indexWeArePlayingFromR = 0;
    
    int indexWeAreAddingToL = 30;
    int indexWeArePlayingFromL = 0;
    
    int totalBuffers = 5000;
    AudioBuffer<float> delay;
    AudioBuffer<float> delay2;
    
    int delayBufferLength;
    
    int delayAmount = 500;
    int delayAmount2 = 500;
    void setDelayAmount(int delayInput);
    void setDelayAmount2(int delayInput);
    //int getBufferSize();
    
    //for parameters======================================================================================
    AudioProcessorValueTreeState treeState;
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    void valueTreePropertyChanged(ValueTree &treeWhosePropertyHasChanged, const Identifier &property) override;
    //    std::atomic<bool> shouldUpdate {false};
    
    //variables
    double currentSampleRate;
    
private:
    
    //variables
    void updateParam(int sRate);
   
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HaastAlphestaelAudioProcessor)
};
