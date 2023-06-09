/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace Neopolitan
{
//==============================================================================

NeopolitanAudioProcessor::NeopolitanAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor(BusesProperties()
   #if !JucePlugin_IsMidiEffect
      #if !JucePlugin_IsSynth
                       .withInput("Input", juce::AudioChannelSet::stereo(), true)
      #endif
                       .withOutput("Output", juce::AudioChannelSet::stereo(), true)
   #endif
                       )
, apvts(*this, nullptr, "Parameters", PluginParameters::createParameterLayout())
, _pluginParameters()
, _flavorNoiseGenerators {apvts.getParameter(PluginParameters::getParameterID(PluginParameters::PID::Vanilla_Gain)), apvts.getParameter(PluginParameters::getParameterID(PluginParameters::PID::Strawberry_Gain)), apvts.getParameter(PluginParameters::getParameterID(PluginParameters::PID::Chocolate_Gain))}
, _freqSpecAnalyzer()
#endif
{
   for (auto i = 0; i < _pluginParameters.size(); ++i)
   {
      // TODO: Cleanup with magic enum?
      const auto pID       = static_cast<PluginParameters::PID>(i);
      _pluginParameters[i] = apvts.getParameter(PluginParameters::getParameterID(pID));
   }
}

NeopolitanAudioProcessor::~NeopolitanAudioProcessor() {}

//==============================================================================
const juce::String NeopolitanAudioProcessor::getName() const { return JucePlugin_Name; }

bool               NeopolitanAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
   return true;
#else
   return false;
#endif
}

bool NeopolitanAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
   return true;
#else
   return false;
#endif
}

bool NeopolitanAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
   return true;
#else
   return false;
#endif
}

double NeopolitanAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int    NeopolitanAudioProcessor::getNumPrograms()
{
   return 1; // NB: some hosts don't cope very well if you tell them there are
             // 0 programs, so this should be at least 1, even if you're not
             // really implementing programs.
}

int NeopolitanAudioProcessor::getCurrentProgram() { return 0; }

// We can enable these functions later if needed. -B
void               NeopolitanAudioProcessor::setCurrentProgram(int index) {}

const juce::String NeopolitanAudioProcessor::getProgramName(int index) { return {}; }

void NeopolitanAudioProcessor::changeProgramName(int index, const juce::String& newName) {}

//==============================================================================
void NeopolitanAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
   // Use this method as the place to do any pre-playback
   // initialisation that you need..
}

void NeopolitanAudioProcessor::releaseResources()
{
   // When playback stops, you can use this as an opportunity to free up any
   // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NeopolitanAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
   #if JucePlugin_IsMidiEffect
   juce::ignoreUnused(layouts);
   return true;
   #else
   // This is the place where you check if the layout is supported.
   // In this template code we only support mono or stereo.
   // Some plugin hosts, such as certain GarageBand versions, will only
   // load plugins that support stereo bus layouts.
   if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
       && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
      return false;

         // This checks if the input layout matches the output layout
      #if !JucePlugin_IsSynth
   if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
      return false;
      #endif

   return true;
   #endif
}
#endif

void NeopolitanAudioProcessor::processBlock(
      juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
   juce::ScopedNoDenormals noDenormals;
   auto                    totalNumInputChannels  = getTotalNumInputChannels();
   auto                    totalNumOutputChannels = getTotalNumOutputChannels();

   // In case we have more outputs than inputs, this code clears any output
   // channels that didn't contain input data, (because these aren't
   // guaranteed to be empty - they may contain garbage).
   // This is here to avoid people getting screaming feedback
   // when they first compile a plugin, but obviously you don't need to keep
   // this code if your algorithm always overwrites all the output channels.
   for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
      buffer.clear(i, 0, buffer.getNumSamples());

   // This is the place where you'd normally do the guts of your plugin's
   // audio processing...
   // Make sure to reset the state if your inner loop is processing
   // the samples and the outer loop is handling the channels.
   // Alternatively, you can process the samples with the channels
   // interleaved by keeping the same state.
   for (int channel = 0; channel < totalNumInputChannels; ++channel)
   {
      auto* channelData = buffer.getWritePointer(channel);

      for (auto sample = 0; sample < buffer.getNumSamples(); ++sample)
      {
         // Add in each of our flavor samples.
         for (auto& flavorNoiseGen : _flavorNoiseGenerators)
         {
            channelData[sample] += flavorNoiseGen.getProcessedSample();
         }

         // Push a copy of the processed/finished sample to the frequency analyzer.
         _freqSpecAnalyzer.pushNextSampleIntoFifo(channelData[sample]);
      }
   }
}

//==============================================================================
juce::AudioProcessorEditor* NeopolitanAudioProcessor::createEditor()
{
   return new NeopolitanAudioProcessorEditor(*this);
}

// Enable these once we start working on saving/loading the plugin state.
//==============================================================================
void NeopolitanAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
   // You should use this method to store your parameters in the memory block.
   // You could do that either as raw data, or use the XML or ValueTree classes
   // as intermediaries to make it easy to save and load complex data.
}

void NeopolitanAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
   // You should use this method to restore your parameters from this memory
   // block, whose contents will have been created by the getStateInformation()
   // call.
}

} // End of namespace Neopolitan.

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
   return new Neopolitan::NeopolitanAudioProcessor();
}
