#pragma once

#include "NeopolitanConstants.h"
#include "NeopolitanLookAndFeel.h"
#include "PluginProcessor.h"
#include <JuceHeader.h>

namespace Neopolitan
{
struct AttachedSlider
{
   using Slider     = juce::Slider;
   using Attachment = juce::SliderParameterAttachment;
   using Component  = juce::Component;

   AttachedSlider(
      NeopolitanAudioProcessor& processor,
      NeopolitanLookAndFeel&    lookAndFeel,
      PluginParams::PID         pID)
      : slider()
      , attachment(*processor.Params()[static_cast<int>(pID)], slider, nullptr)
   {
      slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
      slider.setLookAndFeel(&lookAndFeel);
   }

   Slider     slider;
   Attachment attachment;
};
class FlavorKnob : public juce::Component
{
public:
   FlavorKnob(
      NeopolitanAudioProcessor& processor,
      PluginParams::PID         pID,
      Flavor                    flavor,
      NeopolitanLookAndFeel&    lookAndFeel);

   void           paint(juce::Graphics&) override;
   void           resized() override;
   AttachedSlider _gainDial;

private:
   Flavor      _flavor;
   juce::Label _nameLabel;
   juce::Image _iceCreamImage;
   juce::Image _sprinkleImage;
};

}