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
   NeopolitanAudioProcessor& p)
   : AudioProcessorEditor(&p), audioProcessor(p), _mainScene()
{
   // Make sure that before the constructor has finished, you've set the
   // editor's size to whatever you need it to be.
   setSize(1024, 720);
}

NeopolitanAudioProcessorEditor::~NeopolitanAudioProcessorEditor() {}

}