#pragma once

#include <JuceHeader.h>

namespace Neopolitan
{
class SpectrumAnalyser : public juce::Component
{
public:
   SpectrumAnalyser() : forwardFft(fftOrder) { setOpaque(true); }
   ~SpectrumAnalyser() = default;

   void paint(juce::Graphics& g) override
   {
      g.fillAll(juce::Colours::black);

      g.setOpacity(1.0f);
      g.setColour(juce::Colours::white);
      drawFrame(g);
   }

   void drawFrame(juce::Graphics& g)
   {
      for (int i = 1; i < scopeSize; ++i)
      {
         auto width  = getLocalBounds().getWidth();
         auto height = getLocalBounds().getHeight();

         g.drawLine(
               {(float) juce::jmap(i - 1, 0, scopeSize - 1, 0, width),
                juce::jmap(scopeData[i - 1], 0.0f, 1.0f, (float) height, 0.0f),
                (float) juce::jmap(i, 0, scopeSize - 1, 0, width),
                juce::jmap(scopeData[i], 0.0f, 1.0f, (float) height, 0.0f)});
      }
   }
   void resized() override {}
   enum
   {
      fftOrder  = 11,            // [1]
      fftSize   = 1 << fftOrder, // [2]
      scopeSize = 512            // [3]
   };

private:
   juce::dsp::FFT                      forwardFFT;                // [4]
   juce::dsp::WindowingFunction<float> window;                    // [5]

   float                               fifo[fftSize];             // [6]
   float                               fftData[2 * fftSize];      // [7]
   int                                 fifoIndex         = 0;     // [8]
   bool                                nextFFTBlockReady = false; // [9]
   float                               scopeData[scopeSize];
};

}