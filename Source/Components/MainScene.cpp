#include "MainScene.h"
#include "PluginParameters.h"
#include "PluginProcessor.h"

namespace Neopolitan
{
MainScene::MainScene(NeopolitanAudioProcessor& pluginProcessor, NeopolitanLookAndFeel& lookAndFeel)
   : _flavorKnobs {
      FlavorKnob(pluginProcessor, PluginParams::PID::Vanilla_Mix, Vanilla, lookAndFeel),
      FlavorKnob(pluginProcessor, PluginParams::PID::Strawberry_Mix, Strawberry, lookAndFeel),
      FlavorKnob(pluginProcessor, PluginParams::PID::Chocolate_Mix, Chocolate, lookAndFeel)
   }
{
   _header.setColour(juce::TextButton::buttonColourId, juce::Colours::orange);
   _header.setButtonText("Neopolitan Plugin");
   addAndMakeVisible(_header);
   for (auto& knob : _flavorKnobs)
   {
      addAndMakeVisible(knob);
   }
}

//==============================================================================
void MainScene::paint(juce::Graphics& g)
{
   // (Our component is opaque, so we must completely fill the background with
   // a solid colour).
   g.fillAll(juce::Colour(
      GUI::BACKGROUND_COLOUR_RED, GUI::BACKGROUND_COLOUR_GREEN, GUI::BACKGROUND_COLOUR_BLUE));
}

void MainScene::resized()
{
   // This is the rectangular area that describes the window.
   auto area = getLocalBounds();

   // Trim off some space for the header.
   _header.setBounds(area.removeFromTop(GUI::HEADER_HEIGHT));

   auto w           = static_cast<float>(getWidth());
   auto h           = static_cast<float>(getHeight());
   auto x           = 0.f;
   auto y           = 0.f;
   auto sliderWidth = w / static_cast<float>(Num_Flavors);
   for (auto i = 0; i < Num_Flavors; ++i)
   {
      _flavorKnobs[i].setBounds(juce::Rectangle<float>(x, y, sliderWidth, h).toNearestInt());

      x += sliderWidth;
   }
}

}
