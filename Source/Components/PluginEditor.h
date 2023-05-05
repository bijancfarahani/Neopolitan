/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"

#include "FlavorKnob.h"
#include "NeopolitanConstants.h"
//==============================================================================
/**
 */
namespace Neopolitan
{

class NeopolitanAudioProcessorEditor : public juce::AudioProcessorEditor
{
   public:
   NeopolitanAudioProcessorEditor(NeopolitanAudioProcessor&);
   ~NeopolitanAudioProcessorEditor() override;

   //==============================================================================
   void paint(juce::Graphics&) override;
   void resized() override;

   private:
   // This reference is provided as a quick way for your editor to
   // access the processor object that created it.
   NeopolitanAudioProcessor&           audioProcessor;
   std::array<FlavorKnob, Num_Flavors> _flavorKnobs;

   JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(
      NeopolitanAudioProcessorEditor)
};
}