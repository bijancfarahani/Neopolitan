#include "FlavorKnob.h"

namespace Neopolitan
{

FlavorKnob::FlavorKnob(
      juce::RangedAudioParameter& rangedAudioParameter, NeopolitanLookAndFeel& lookAndFeel)
: _gainDial(rangedAudioParameter, lookAndFeel)
{
   addAndMakeVisible(_gainDial.slider);
}

void FlavorKnob::resized()
{
   _gainDial.slider.setBounds(
         juce::Rectangle<float>(
               0, 0, static_cast<float>(getWidth()), static_cast<float>(getHeight()))
               .toNearestInt());
}

}