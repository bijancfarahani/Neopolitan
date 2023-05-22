#pragma once

#include "FrequencySpectrumAnalyzer.h"
#include <JuceHeader.h>

namespace Neopolitan
{
class FrequencySpectrumAnalyzer;

class FrequencySpectrumDisplay
: public juce::Component
, juce::Timer
{
public:
   FrequencySpectrumDisplay(FrequencySpectrumAnalyzer& freqSpectrumAnalyzer);
   ~FrequencySpectrumDisplay() = default;

   void paint(juce::Graphics& g) override;

   void timerCallback() override;

   void resized() override {}

private:
private:
   void                       _drawFrame(juce::Graphics& g);

   void                       _drawNextFrameOfSpectrum();

   FrequencySpectrumAnalyzer& _freqSpectrumAnalyzer;
};

}