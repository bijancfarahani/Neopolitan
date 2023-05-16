#include "FlavorKnob.h"

namespace Neopolitan
{

FlavorKnob::FlavorKnob(
   NeopolitanAudioProcessor& pluginProcessor,
   PluginParams::PID         pID,
   Flavor                    flavor,
   NeopolitanLookAndFeel&    lookAndFeel)
   : _gainDial(pluginProcessor, lookAndFeel, pID)
   , _flavor(flavor)
{
   //setSize(300, 300);
   // _gainDial.slider.setSize(300, 300);

   addAndMakeVisible(_nameLabel);
   addAndMakeVisible(_gainDial.slider);
}

void FlavorKnob::paint(juce::Graphics& g)
{
   // fill
}

void FlavorKnob::resized()
{
   _gainDial.slider.setBounds(juce::Rectangle<float>(0, 0, getWidth(), getHeight()).toNearestInt());
}

}