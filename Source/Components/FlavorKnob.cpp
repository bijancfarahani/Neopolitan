#include "FlavorKnob.h"

namespace Neopolitan
{

FlavorKnob::FlavorKnob(NeopolitanAudioProcessor& pluginProcessor, PluginParams::PID pID, NeopolitanLookAndFeel& lookAndFeel) : _gainDial(pluginProcessor, lookAndFeel, pID)
{
   //setSize(300, 300);
   // _gainDial.slider.setSize(300, 300);

   addAndMakeVisible(_nameLabel);
   addAndMakeVisible(_gainDial.slider);
}

void FlavorKnob::initialize(FlavorCode flavorCode)
{
   _flavorCode = flavorCode;
}

void FlavorKnob::paint(juce::Graphics& g)
{
}

void FlavorKnob::resized()
{
   _gainDial.slider.setBounds(juce::Rectangle<float>(0, 0, getWidth(), getHeight()).toNearestInt());
}

}