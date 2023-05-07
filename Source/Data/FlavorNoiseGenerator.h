#pragma once

#include "NeopolitanConstants.h"
#include <JuceHeader.h>

namespace Neopolitan
{

class FlavorNoiseGenerator
{
public:
   FlavorNoiseGenerator() = default;
   ~FlavorNoiseGenerator() = default;

   float getSample()
   {
      _vanillaSample = _random.nextFloat() * 0.25f - 0.125f;

      return std::accumulate(_flavorSamples.begin(), _flavorSamples.end(), 0.0);
   }

private:
   juce::Random                   _random;
   std::array<float, Num_Flavors> _flavorSamples {};

   float& _vanillaSample    = _flavorSamples[0];
   float& _strawberrySample = _flavorSamples[1];
   float& _chocolateSample  = _flavorSamples[2];
};

class FlavorNoise
{

    public:
        FlavorNoise() {
        }
        ~FlavorNoise() = default;
    private:

    juce::AudioParameterFloat* _gain;
};
}