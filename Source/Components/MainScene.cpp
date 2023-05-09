#include "MainScene.h"

namespace Neopolitan
{
MainScene::MainScene()
{
   _header.setColour(juce::TextButton::buttonColourId, juce::Colours::orange);
   _header.setButtonText("Neopolitan Plugin");
   addAndMakeVisible(_header);

   for (auto& knob : _flavorKnobs)
   {
     // addAndMakeVisible(knob);
   }
   _flavorKnobs[Vanilla].initialize(Vanilla);
   _flavorKnobs[Strawberry].initialize(Strawberry);
   _flavorKnobs[Chocolate].initialize(Chocolate);
}

//==============================================================================
void MainScene::paint(juce::Graphics& g)
{
   // (Our component is opaque, so we must completely fill the background with
   // a solid colour).
   g.fillAll(juce::Colour(GUI::BACKGROUND_COLOUR_RED, GUI::BACKGROUND_COLOUR_GREEN, GUI::BACKGROUND_COLOUR_BLUE));

   // Draw the flavor knobs
   for (auto& knob : _flavorKnobs)
   {
      knob.paint(g);
   }
}

void MainScene::resized()
{
   // This is the rectangular area that describes the window.
   auto area = getLocalBounds();

   // Trim off some space for the header.
   _header.setBounds(area.removeFromTop(GUI::HEADER_HEIGHT));

   for (auto& knob : _flavorKnobs)
   {
      knob.resized();
   }
}

}
