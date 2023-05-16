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

NeopolitanAudioProcessorEditor::NeopolitanAudioProcessorEditor(NeopolitanAudioProcessor& p)
   : AudioProcessorEditor(&p)
   , audioProcessor(p)
   , _mainScene(p, _lookAndFeel)
{
   setSize(GUI::DEFAULT_WINDOW_WIDTH, GUI::DEFAULT_WINDOW_HEIGHT);

   _mainScene.setSize(getWidth(), getHeight());
   addAndMakeVisible(_mainScene);
}

NeopolitanAudioProcessorEditor::~NeopolitanAudioProcessorEditor() {}

}