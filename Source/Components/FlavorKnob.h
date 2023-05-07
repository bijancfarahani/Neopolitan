#pragma once

#include "DecibelSlider.h"
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
   FlavorCode    _flavorCode;
   DecibelSlider _gainDial;
   juce::Image   _iceCreamImage;
   juce::Image   _sprinkleImage;
};

}