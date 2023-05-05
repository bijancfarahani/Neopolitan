#include "FlavorKnob.h"

namespace Neopolitan
{

FlavorKnob::FlavorKnob()
{
   addAndMakeVisible(_nameLabel);
   _gainDial.setSliderStyle(juce::Slider::Rotary);
   addAndMakeVisible(_gainDial);
}

void FlavorKnob::initialize(FlavorCode flavorCode)
{
   _flavorCode = flavorCode;

   // Set the label name with the flavor.
   juce::String _flavorName {};
   switch (flavorCode)
   {
   case Vanilla:
   {
      _flavorName    = "Vanilla";
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
   default:
   {
      _flavorName = "You fucked up";
      break;
   }
   }
   _nameLabel.setText(_flavorName, juce::dontSendNotification);

   _gainDial.setTextValueSuffix("dB");
   //_gainDial.onValueChange = [idx, &slider, this] { _flavorLevels[idx] =
   // juce::Decibels::decibelsToGain((float)slider.getValue()); };
   _gainDial.setRange(-100.0f, 0.0f);
   _gainDial.setValue(-100.0f, juce::dontSendNotification);
}

void FlavorKnob::paint(juce::Graphics& g)
{
   switch (_flavorCode)
   {
   case Vanilla:
   {
      g.drawImageAt(_iceCreamImage, 200, 200);
      g.drawImageAt(_sprinkleImage, 200, 200);
   }
   case Strawberry:
   {
   }
   case Chocolate:
   {
   }
   default:
   {
      // TODO: Paint a PATO.
   }
   }
}

void FlavorKnob::resized()
{
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
   default:
   {
      // TODO: Paint a PATO.
   }
   }
}

}