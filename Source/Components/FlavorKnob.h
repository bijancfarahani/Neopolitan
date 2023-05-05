#pragma once

#include <JuceHeader.h>
#include "NeopolitanConstants.h"

namespace Neopolitan
{

class FlavorKnob : public juce::Component
{
   public:
   FlavorKnob();

   void initialize(FlavorCode flavorCode);

   void paint(juce::Graphics&) override;
   void resized() override;

   private:
   FlavorCode   _flavorCode;
   juce::Label  _nameLabel;
   juce::Slider _gainSlider;
   juce::Image  _iceCreamImage;
   juce::Image  _sprinkleImage;
};

}