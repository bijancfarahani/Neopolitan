#pragma once

#include "FlavorKnob.h"
#include "FrequencySpectrumDisplay.h"
#include "NeopolitanConstants.h"
#include "NeopolitanGUIConstants.h"
#include "NeopolitanLookAndFeel.h"
#include <JuceHeader.h>

namespace Neopolitan
{

/// @brief
/// This class describes the rectangle which
/// emcompasses the GUI window for the plugin.
/// This large rectange is subdivided in various
/// components, which are owned by this class.
class MainScene : public juce::Component
{
public:
   MainScene(NeopolitanAudioProcessor& pluginProcessor, NeopolitanLookAndFeel& lookAndFeel);

   void paint(juce::Graphics& g) override;
   void resized() override;

private:
   std::array<FlavorKnob, NUM_FLAVORS> _flavorKnobs;

   juce::TextButton                    _header;

   FrequencySpectrumDisplay            _freqSpectrumDisplay;
};

}