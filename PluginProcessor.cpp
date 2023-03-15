/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HaastAlphestaelAudioProcessor::HaastAlphestaelAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
:  currentSampleRate(0.0f),

AudioProcessor(BusesProperties().withInput("Main", AudioChannelSet::stereo())
               .withOutput("Main", AudioChannelSet::stereo()))       , treeState(*this, nullptr, "PARAM",createParameterLayout()              )
#endif
{
    //value tree to listen to this component
     treeState.state.addListener(this);
}

HaastAlphestaelAudioProcessor::~HaastAlphestaelAudioProcessor()
{
   
}

//==============================================================================
AudioProcessorValueTreeState::ParameterLayout HaastAlphestaelAudioProcessor::createParameterLayout()
{
    //Create arraylist of audio parameters
    std::vector <std::unique_ptr<RangedAudioParameter>> params;
    
    //add our parameters
    params.push_back(std::make_unique<AudioParameterFloat>(DELAY_ID, DELAY_NAME, 0.0, 1.0f, 0.0f));
    params.push_back(std::make_unique<AudioParameterFloat>(DELAY_ID2, DELAY_NAME2, 0.0, 1.0f, 0.0f));
    
    return {params.begin(), params.end()};
    
}
const String HaastAlphestaelAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HaastAlphestaelAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HaastAlphestaelAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HaastAlphestaelAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double HaastAlphestaelAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HaastAlphestaelAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int HaastAlphestaelAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HaastAlphestaelAudioProcessor::setCurrentProgram (int index)
{
}

const String HaastAlphestaelAudioProcessor::getProgramName (int index)
{
    return {};
}

void HaastAlphestaelAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void HaastAlphestaelAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //set current sample rate
    currentSampleRate = sampleRate ;
    
    
    
    //delay buffer size needs to be the size of 0.04 seconds (to do 40ms of delay)
    //buffer time length is numsamps/currentsamplerate
    
    //number of buffers to pass 0.04s is 0.04/buffer time in length
    
    //numberofsamples to pass is noOfBuffers * bufferSize
    
//    float bufferTime = samplesPerBlock/currentSampleRate;
//    float noOfBuffers = 0.05/bufferTime;
//    float totalDelaySamps = noOfBuffers * samplesPerBlock;
    
    
    //set delay buffer sizes
    delayBufferLength = (2048*totalBuffers);
    
    delay.setSize(2,  delayBufferLength);
    
    delay2.setSize(2, delayBufferLength);
 
    updateParam(sampleRate);
    
}

void HaastAlphestaelAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HaastAlphestaelAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void HaastAlphestaelAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    //define audio buffer
    AudioSampleBuffer mainInputOutput = getBusBuffer(buffer, true, 0);
    
    ScopedNoDenormals noDenormals;
    
    auto mainInputChannels = mainInputOutput.getNumChannels();
    auto mainOutputChannels = mainInputOutput.getNumChannels();
    
    //clear main
    for (auto i = mainInputChannels; i < mainOutputChannels; ++i)
        mainInputOutput.clear(i, 0, mainInputOutput.getNumSamples());
    
    
    //get pointers for writing to delay and main buffers
    auto* delayR = delay.getWritePointer(1);
    auto* delayL = delay2.getWritePointer(0);
    
    auto* channelDataR = buffer.getWritePointer(1);
    auto* channelDataL = buffer.getWritePointer(0);
    
    //update delay amount
    indexWeAreAddingToR = indexWeArePlayingFromR + delayAmount;
    indexWeAreAddingToL = indexWeArePlayingFromL + delayAmount2;
    
    
    //TAKE CURRENT DATA, STORE IT LATER IN DELAY BUFFER
    for(int i=0;i<buffer.getNumSamples();i++)
    {
        //incremement
        indexWeAreAddingToR = indexWeAreAddingToR +1;
//        indexWeAreAddingToR = indexWeArePlayingFromR + delayAmount;
        
        //if we reach end of buffer, reset
        if(indexWeAreAddingToR>delayBufferLength)
        {
                        indexWeAreAddingToR  = 0;
//            indexWeAreAddingToR = indexWeAreAddingToR-delayBufferLength;
        }
        
        //put data in delay buffer
        delayR[indexWeAreAddingToR] = channelDataR[i];
     
    }
    
    //ditto for left channel
    for(int i=0;i<buffer.getNumSamples();i++)
    {
        //incremement
        indexWeAreAddingToL = indexWeAreAddingToL +1;
        //        indexWeAreAddingToR = indexWeArePlayingFromR + delayAmount;

        //if we reach end of buffer, reset
        if(indexWeAreAddingToL>delayBufferLength)
        {
            indexWeAreAddingToL  = 0;
            //            indexWeAreAddingToR = indexWeAreAddingToR-delayBufferLength;
        }

        //put data in delay buffer
        delayL[indexWeAreAddingToL] = channelDataL[i];

    }
    

    //PLAY CURRENT DATA (PREVIOUSLY STORED) FROM DELAY BUFFER
    for(int i=0;i<buffer.getNumSamples();i++)
    {
        indexWeArePlayingFromR = indexWeArePlayingFromR  +1;
        
        if(indexWeArePlayingFromR>(delayBufferLength))
        {
            indexWeArePlayingFromR = 0;
        }
        channelDataR[i] = delayR[indexWeArePlayingFromR];
        
    }
    
    //"" "" for left channel
    for(int i=0;i<buffer.getNumSamples();i++)
    {
        indexWeArePlayingFromL = indexWeArePlayingFromL  +1;
        
        if(indexWeArePlayingFromL>(delayBufferLength))
        {
            indexWeArePlayingFromL = 0;
        }
        channelDataL[i] = delayL[indexWeArePlayingFromL];
        
    }


    
}

//==============================================================================
bool HaastAlphestaelAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* HaastAlphestaelAudioProcessor::createEditor()
{
    return new HaastAlphestaelAudioProcessorEditor (*this);
}

//==============================================================================
void HaastAlphestaelAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = treeState.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void HaastAlphestaelAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (treeState.state.getType()))
            treeState.replaceState (juce::ValueTree::fromXml (*xmlState));
    
    updateParam(currentSampleRate);
}

void HaastAlphestaelAudioProcessor::updateParam(int sRate)
{
    delayAmount = sRate * 0.025 * treeState.getRawParameterValue("DELAY")->load();
    
    delayAmount2 = sRate * 0.025 * treeState.getRawParameterValue("DELAY2")->load();

}


void HaastAlphestaelAudioProcessor::setDelayAmount(int delayInput)
{
    delayAmount = delayInput;
    
    
}
void HaastAlphestaelAudioProcessor::setDelayAmount2(int delayInput)
{
    
    delayAmount2 = delayInput;
}


void HaastAlphestaelAudioProcessor::valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged, const Identifier& property)
{
    updateParam(currentSampleRate);
}
//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HaastAlphestaelAudioProcessor();
}
