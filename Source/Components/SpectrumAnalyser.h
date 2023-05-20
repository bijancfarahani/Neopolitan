#pragma once

#include "Spec.h"
#include <JuceHeader.h>

namespace Neopolitan
{
class Spec;

class SpectrumAnalyser
: public juce::Component
, juce::Timer
{
public:
   SpectrumAnalyser(Spec& spec) : _spec(spec) {}
   ~SpectrumAnalyser() = default;

   void paint(juce::Graphics& g) override
   {
      g.fillAll(juce::Colours::black);

      g.setOpacity(1.0f);
      g.setColour(juce::Colours::white);
      drawFrame(g);
   }

   void timerCallback() override
   {
      if (_spec.getNextFFTBlockReady())
      {
         drawNextFrameOfSpectrum();
         _spec.getNextFFTBlockReady() = false;
         repaint();
      }
   }

   void drawFrame(juce::Graphics& g)
   {
      for (int i = 1; i < _spec.getScopeSize(); ++i)
      {
         auto width  = getLocalBounds().getWidth();
         auto height = getLocalBounds().getHeight();
         std::cout << "scopeData: " << _spec.getScopeData()[i - 1] << std::endl;
         g.drawLine(
               {(float) juce::jmap(i - 1, 0, _spec.getScopeSize() - 1, 0, width),
                juce::jmap(_spec.getScopeData()[i - 1], 0.0f, 1.0f, (float) height, 0.0f),
                (float) juce::jmap(i, 0, _spec.getScopeSize() - 1, 0, width),
                juce::jmap(_spec.getScopeData()[i], 0.0f, 1.0f, (float) height, 0.0f)});
      }
   }

   void drawNextFrameOfSpectrum()
   {
      // first apply a windowing function to our data
      _spec.getWindow().multiplyWithWindowingTable(_spec.getFftData(), _spec.fftSize); // [1]

      // then render our FFT data..
      _spec.getForwardFFT().performFrequencyOnlyForwardTransform(_spec.getFftData()); // [2]

      auto mindB = -100.0f;
      auto maxdB = 0.0f;

      for (int i = 0; i < _spec.getScopeSize(); ++i) // [3]
      {
         auto skewedProportionX =
               1.0f - std::exp(std::log(1.0f - (float) i / (float) _spec.getScopeSize()) * 0.2f);
         auto fftDataIndex = juce::jlimit(
               0, _spec.fftSize / 2, (int) (skewedProportionX * (float) _spec.fftSize * 0.5f));
         auto level = juce::jmap(
               juce::jlimit(
                     mindB,
                     maxdB,
                     juce::Decibels::gainToDecibels(_spec.getFftData()[fftDataIndex])
                           - juce::Decibels::gainToDecibels((float) _spec.fftSize)),
               mindB,
               maxdB,
               0.0f,
               1.0f);

         _spec.getScopeData()[i] = level; // [4]
      }
   }

   void resized() override {}

private:
   Spec& _spec;
};

}