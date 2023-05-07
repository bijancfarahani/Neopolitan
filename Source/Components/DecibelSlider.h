#pragma once

#include "NeopolitanConstants.h"
#include <JuceHeader.h>

namespace Neopolitan
{

class DecibelSlider : public juce::Slider
{
public:
   DecibelSlider()
   {
      addAndMakeVisible(_nameLabel);
      _nameLabel.attachToComponent(this, true);
      //addListener(this);
      setSize(300, 300);
      setSliderStyle(juce::Slider::Rotary);
      setTextValueSuffix("dB");
      // Controls
      //onValueChange = [idx, &slider, this] { _flavorLevels[idx] =
      // juce::Decibels::decibelsToGain((float)slider.getValue()); };
      setRange(Negative_Infinity_dB, -12);
      //setValue(-100.0f, juce::dontSendNotification);
      setValue(juce::Decibels::gainToDecibels(_volumeLevel));
      onValueChange = [this] { setVolumeLevel(juce::Decibels::decibelsToGain(static_cast<float>(_volumeLevel))); };
   }

   double getValueFromText(const juce::String& text) override
   {
      auto decibelText = text.upToFirstOccurrenceOf("dB", false, false).trim(); // [1]

      return decibelText.equalsIgnoreCase("-INF") ? Negative_Infinity_dB
                                                  : decibelText.getDoubleValue(); // [2]
   }

   juce::String getTextFromValue(double value) override
   {
      return juce::Decibels::toString(value);
   }

   float VolumeLevel() const { return _volumeLevel; }

   void setVolumeLevel(float volumeDb)
   {
      _volumeLevel = volumeDb;
   }

private:
   float       _volumeLevel { Negative_Infinity_dB };
   juce::Label _nameLabel;

   JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DecibelSlider)
};

}