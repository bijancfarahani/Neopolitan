#pragma once
#include <JuceHeader.h>
namespace Neopolitan
{

class FlavorNoiseGenerator
{
public:
   FlavorNoiseGenerator(juce::RangedAudioParameter* flavorGainParameter)
   : _flavorGainParameter(flavorGainParameter)
   {}
   ~FlavorNoiseGenerator() = default;

   float getProcessedSample()
   {
      // NOTE: This sample is just for white noise.
      // Fill the required number of samples with noise between -0.125 and +0.125
      auto       sample     = _random.nextFloat() * 0.25f - 0.125f;
      const auto gainDbNorm = _flavorGainParameter->getValue();
      const auto gainDb  = _flavorGainParameter->getNormalisableRange().convertFrom0to1(gainDbNorm);
      const auto gain    = juce::Decibels::decibelsToGain(gainDb);
      sample            *= gain;
      return sample;
   }

private:
   // Plugin-wide random number generator.  Currently the entire plugin should use
   // this object, but later on we can have specific RNG for each flavor, etc.
   juce::Random _random {};

   // Reference to the GUI parameter
   juce::RangedAudioParameter* _flavorGainParameter;
};
}