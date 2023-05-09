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
   : AudioProcessorEditor(&p), audioProcessor(p), _mainScene(),
   sliders{AttachedSlider(p, param::PID::GainWet), AttachedSlider(p, param::PID::Frequency)}
{
   // Make sure that before the constructor has finished, you've set the
   // editor's size to whatever you need it to be.
   setSize(1024, 720);
    for (auto i = 0; i < sliders.size(); ++i)
    {
        auto& slider = sliders[i];

       addAndMakeVisible(slider.slider);
    }
   _mainScene.setSize(getWidth(), getHeight());
   //addAndMakeVisible(_mainScene);
}

NeopolitanAudioProcessorEditor::~NeopolitanAudioProcessorEditor() {}

}