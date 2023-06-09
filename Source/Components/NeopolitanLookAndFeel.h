#pragma once

#include <JuceHeader.h>
namespace Neopolitan
{

class NeopolitanLookAndFeel : public juce::LookAndFeel_V4
{
public:
   NeopolitanLookAndFeel() { setColour(juce::Slider::thumbColourId, juce::Colours::red); }

   void drawRotarySlider(
      juce::Graphics& g,
      int             x,
      int             y,
      int             width,
      int             height,
      float           sliderPos,
      const float     rotaryStartAngle,
      const float     rotaryEndAngle,
      juce::Slider&) override
   {
      auto radius  = (float) juce::jmin(width / 2, height / 2) - 4.0f;
      auto centreX = (float) x + (float) width * 0.5f;
      auto centreY = (float) y + (float) height * 0.5f;
      auto rx      = centreX - radius;
      auto ry      = centreY - radius;
      auto rw      = radius * 2.0f;
      auto angle   = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

      // outline
      g.setColour(juce::Colours::red);
      g.drawEllipse(rx, ry, rw, rw, 1.0f);
      g.fillEllipse(rx, ry, rw, rw);
      juce::Path p;
      auto       pointerLength    = radius * 0.33f;
      auto       pointerThickness = 2.0f;
      p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
      p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

      // pointer
      g.setColour(juce::Colours::yellow);
      g.fillPath(p);
   }

   juce::Colour _flavorColour {};
};

}