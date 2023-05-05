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
   : AudioProcessorEditor(&p), audioProcessor(p)
{
   // Make sure that before the constructor has finished, you've set the
   // editor's size to whatever you need it to be.
   setSize(1024, 720);

   for (auto& knob : _flavorKnobs)
   {
      addAndMakeVisible(knob);
   }
   _flavorKnobs[Vanilla].initialize(Vanilla);
   _flavorKnobs[Strawberry].initialize(Strawberry);
   _flavorKnobs[Chocolate].initialize(Chocolate);
}

NeopolitanAudioProcessorEditor::~NeopolitanAudioProcessorEditor() {}

//==============================================================================
void NeopolitanAudioProcessorEditor::paint(juce::Graphics& g)
{
   // (Our component is opaque, so we must completely fill the background with
   // a solid colour) Fill it with this color: #66ffcc.  Below numbers are
   // R,G,B. constexpr auto BACKGROUND_COLOUR_RBG = {152, 184, 174};

   g.fillAll(juce::Colour { 152, 184, 174 });

   // This sets the text.
   // g.setColour (juce::Colours::white);
   // g.setFont (15.0f);
   // g.drawFittedText ("Hello World!", getLocalBounds(),
   // juce::Justification::centred, 1);

   // Draw the flavor knobs
   for (auto& knob : _flavorKnobs)
   {
      knob.paint(g);
   }
}

void NeopolitanAudioProcessorEditor::resized()
{
   // This is generally where you'll want to lay out the positions of any
   // subcomponents in your editor..
   for (auto& knob : _flavorKnobs)
   {
      knob.resized();
   }
}

}