/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
namespace Neopolitan
{

NeopolitanAudioProcessorEditor::NeopolitanAudioProcessorEditor(
   NeopolitanAudioProcessor& p, juce::AudioProcessorValueTreeState& valueStateTree)
   : AudioProcessorEditor(&p), _audioProcessor(p), _mainScene(),
   _valueStateTree(valueStateTree)
{
   // Make sure that before the constructor has finished, you've set the
   // editor's size to whatever you need it to be.
   setSize(1024, 720);

   _mainScene.setSize(getWidth(), getHeight());
   addAndMakeVisible(_mainScene);
}

NeopolitanAudioProcessorEditor::~NeopolitanAudioProcessorEditor() {}

}