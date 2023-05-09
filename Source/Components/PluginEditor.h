/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <array>

#include <JuceHeader.h>

#include "PluginProcessor.h"

#include "FlavorKnob.h"
#include "MainScene.h"
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
   void paint(juce::Graphics& g) override { _mainScene.paint(g); }
   void resized() override { _mainScene.resized(); }

private:
   // This reference is provided as a quick way for your editor to
   // access the processor object that created it.
   NeopolitanAudioProcessor& audioProcessor;
   MainScene                 _mainScene;

   JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(
      NeopolitanAudioProcessorEditor)
};
}