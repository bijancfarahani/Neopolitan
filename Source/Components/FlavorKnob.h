#pragma once

#include "NeopolitanConstants.h"
#include <JuceHeader.h>

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
   juce::Slider _gainDial;
   juce::Image  _iceCreamImage;
   juce::Image  _sprinkleImage;
};

}