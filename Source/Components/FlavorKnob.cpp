#include "FlavorKnob.h"

namespace Neopolitan
{

FlavorKnob::FlavorKnob() : _gainDial()
{
   setSize(300, 300);

   // Visuals
   // Configure the rotary dials on each flavor knob.
   addAndMakeVisible(_gainDial);
   //_gainDial.addListener(this);
   _gainDial.setSize(300, 300);
   _gainDial.setSliderStyle(juce::Slider::Rotary);
   _gainDial.setTextValueSuffix("dB");
   // Controls
   //_gainDial.onValueChange = [idx, &slider, this] { _flavorLevels[idx] =
   // juce::Decibels::decibelsToGain((float)slider.getValue()); };
   _gainDial.setRange(Negative_Infinity_dB, -12);
   //_gainDial.setValue(-100.0f, juce::dontSendNotification);
   _gainDial.setValue(juce::Decibels::gainToDecibels(_gainDial.VolumeLevel()));
   _gainDial.onValueChange = [this] { _gainDial.setVolumeLevel(juce::Decibels::decibelsToGain(static_cast<float>(_gainDial.getValue()))); };
}

void FlavorKnob::initialize(FlavorCode flavorCode)
{
   _flavorCode = flavorCode;

   // Set the label name with the flavor.
   // actually dont
   juce::String _flavorName {};
   switch (flavorCode)
   {
   case Vanilla:
   {
      _flavorName    = "Vanilla"; // remove these
      _iceCreamImage = juce::ImageFileFormat::loadFrom(
         BinaryData::icecream_circle1_png,
         BinaryData::icecream_circle1_pngSize);
      _sprinkleImage = juce::ImageFileFormat::loadFrom(
         BinaryData::icecream_sprinkle1_png,
         BinaryData::icecream_sprinkle1_pngSize);

      break;
   }
   case Strawberry:
   {
      _flavorName    = "Strawberry";
      _iceCreamImage = juce::ImageFileFormat::loadFrom(
         BinaryData::icecream_circle2_png,
         BinaryData::icecream_circle2_pngSize);
      _sprinkleImage = juce::ImageFileFormat::loadFrom(
         BinaryData::icecream_sprinkle2_png,
         BinaryData::icecream_sprinkle2_pngSize);

      break;
   }
   case Chocolate:
   {
      _flavorName    = "Chocolate";
      _iceCreamImage = juce::ImageFileFormat::loadFrom(
         BinaryData::icecream_circle3_png,
         BinaryData::icecream_circle3_pngSize);
      _sprinkleImage = juce::ImageFileFormat::loadFrom(
         BinaryData::icecream_sprinkle3_png,
         BinaryData::icecream_sprinkle3_pngSize);

      break;
   }
   }
   //_nameLabel.setText(_flavorName, juce::dontSendNotification);
}

void FlavorKnob::paint(juce::Graphics& g)
{
   int x = 0;
   switch (_flavorCode)
   {
   case Vanilla:
   {
      x = 200;
      break;
   }
   case Strawberry:
   {
      x = 350;
      break;
   }
   case Chocolate:
   {
      x = 500;
      break;
   }
   }
   g.drawImageAt(_iceCreamImage, x, 200);
   g.drawImageAt(_sprinkleImage, x, 200);
}

void FlavorKnob::resized()
{
   auto area = getLocalBounds();

   _gainDial.setBounds(area.reduced(10));
   switch (_flavorCode)
   {
   case Vanilla:
   {
      setBounds(256, 360, 150, 150);
   }
   case Strawberry:
   {
   }
   case Chocolate:
   {
   }
   }
}

}