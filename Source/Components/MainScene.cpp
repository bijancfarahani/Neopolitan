#include "MainScene.h"
#include "PluginParameters.h"
#include "PluginProcessor.h"

namespace Neopolitan
{
MainScene::MainScene(NeopolitanAudioProcessor& pluginProcessor, NeopolitanLookAndFeel& lookAndFeel)
: _flavorKnobs {FlavorKnob(pluginProcessor.getPluginParameter(PluginParameters::PID::Vanilla_Mix), lookAndFeel), FlavorKnob(pluginProcessor.getPluginParameter(PluginParameters::PID::Strawberry_Mix), lookAndFeel), FlavorKnob(pluginProcessor.getPluginParameter(PluginParameters::PID::Chocolate_Mix), lookAndFeel)}
, _freqSpectrumDisplay(pluginProcessor.getSpectrumAnalyzer())
{
   // Header
   _header.setColour(juce::TextButton::buttonColourId, juce::Colours::orange);
   _header.setButtonText("Neopolitan Plugin");
   addAndMakeVisible(_header);

   // Flavor Mix Knobs
   for (auto& knob : _flavorKnobs)
   {
      addAndMakeVisible(knob);
   }

   // Frequency Spectrum Display
   addAndMakeVisible(_freqSpectrumDisplay);
}

//==============================================================================
void MainScene::paint(juce::Graphics& g)
{
   g.fillAll(juce::Colour(
         GUI::BACKGROUND_COLOUR_RED, GUI::BACKGROUND_COLOUR_GREEN, GUI::BACKGROUND_COLOUR_BLUE));
}

void MainScene::resized()
{
   // This is the rectangular area that describes the window.
   auto area = getLocalBounds();

   // Trim off some space for the header.
   _header.setBounds(area.removeFromTop(GUI::HEADER_HEIGHT));

   // Flavor Knobs
   auto       x           = 0.f;
   auto       y           = 0.f;
   const auto sliderWidth = static_cast<float>(area.getWidth()) / static_cast<float>(Num_Flavors);
   for (auto i = 0; i < Num_Flavors; ++i)
   {
      _flavorKnobs[i].setBounds(
            juce::Rectangle<float>(x, y, sliderWidth, static_cast<float>(area.getHeight() / 3))
                  .toNearestInt());

      x += sliderWidth;
   }

   _freqSpectrumDisplay.setBounds(area.removeFromBottom(400));
}

}
