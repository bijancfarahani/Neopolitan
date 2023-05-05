/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"

//==============================================================================
/**
 */

enum FlavorCode : uint8_t {
   Vanilla,
   Strawberry,
   Chocolate,
   Num_Flavors
};

class FlavorKnob : public juce::Component
{
   public:
   FlavorKnob();

   void initialize(FlavorCode flavorCode);

   void paint(juce::Graphics&) override;
   void resized() override;

   private:
   FlavorCode   _flavorCode;
   juce::Label  _nameLabel;
   juce::Slider _gainSlider;
   juce::Image  _iceCreamImage;
   juce::Image  _sprinkleImage;
};

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
