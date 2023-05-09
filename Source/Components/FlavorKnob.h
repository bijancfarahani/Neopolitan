#pragma once

#include "NeopolitanConstants.h"
#include "PluginProcessor.h"
#include <JuceHeader.h>

namespace Neopolitan
{
struct AttachedSlider
{
   using Slider     = juce::Slider;
   using Attachment = juce::SliderParameterAttachment;
   using Component  = juce::Component;

   AttachedSlider(NeopolitanAudioProcessor& processor, param::PID pID) : slider(),
                                                                         attachment(*processor.Params()[static_cast<int>(pID)], slider, nullptr)
   {
      slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
   }

   Slider     slider;
   Attachment attachment;
};
class FlavorKnob : public juce::Component
{
public:
   FlavorKnob(NeopolitanAudioProcessor& processor, param::PID pID);

   void initialize(FlavorCode flavorCode);

   void           paint(juce::Graphics&) override;
   void           resized() override;
   AttachedSlider _gainDial;

private:
   FlavorCode  _flavorCode;
   juce::Label _nameLabel;
   juce::Image _iceCreamImage;
   juce::Image _sprinkleImage;
};

}