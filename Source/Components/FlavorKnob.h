#pragma once


#include "NeopolitanLookAndFeel.h"
#include "PluginProcessor.h"
#include <JuceHeader.h>

namespace Neopolitan
{
struct AttachedSlider
{
   AttachedSlider(
         juce::RangedAudioParameter& rangedAudioParameter, NeopolitanLookAndFeel& lookAndFeel)
   : slider()
   , attachment(rangedAudioParameter, slider, nullptr)
   {
      slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
      slider.setLookAndFeel(&lookAndFeel);
   }

   juce::Slider                    slider;
   juce::SliderParameterAttachment attachment;
};
class FlavorKnob : public juce::Component
{
public:
   FlavorKnob(juce::RangedAudioParameter& rangedAudioParameter, NeopolitanLookAndFeel& lookAndFeel);

   void           paint(juce::Graphics&) override {}
   void           resized() override;
   AttachedSlider _gainDial;

private:
};

}