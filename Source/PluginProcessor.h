/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "FrequencySpectrumAnalyzer.h"
#include "PluginParameters.h"
#include <JuceHeader.h>

//==============================================================================
/**
 */
namespace Neopolitan
{
class NeopolitanAudioProcessor
: public juce::AudioProcessor
#if JucePlugin_Enable_ARA
, public juce::AudioProcessorARAExtension
#endif
{
public:
   //==============================================================================
   NeopolitanAudioProcessor();
   ~NeopolitanAudioProcessor() override;

   //==============================================================================
   void prepareToPlay(double sampleRate, int samplesPerBlock) override;
   void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
   bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

   void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

   //==============================================================================
   juce::AudioProcessorEditor* createEditor() override;
   bool                        hasEditor() const { return true; }

   //==============================================================================
   const juce::String getName() const override;

   bool               acceptsMidi() const override;
   bool               producesMidi() const override;
   bool               isMidiEffect() const override;
   double             getTailLengthSeconds() const override;

   //==============================================================================
   int                getNumPrograms() override;
   int                getCurrentProgram() override;
   void               setCurrentProgram(int index) override;
   const juce::String getProgramName(int index) override;
   void               changeProgramName(int index, const juce::String& newName) override;

   //==============================================================================
   // TODO: Feature: Save/load the plugin state.
   void                        getStateInformation(juce::MemoryBlock& destData) override;
   void                        setStateInformation(const void* data, int sizeInBytes) override;

   juce::RangedAudioParameter& getPluginParameter(PluginParameters::PID pid)
   {
      return *(_pluginParameters[magic_enum::enum_index<PluginParameters::PID>(pid).value()]);
   }

   FrequencySpectrumAnalyzer& getSpectrumAnalyzer() { return _spec; }

private:
   //==============================================================================

   juce::AudioProcessorValueTreeState                                   apvts;
   std::array<juce::RangedAudioParameter*, PluginParameters::NumParams> _pluginParameters;
   juce::Random                                                         _random;
   FrequencySpectrumAnalyzer                                            _spec;

   JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NeopolitanAudioProcessor)
};

}