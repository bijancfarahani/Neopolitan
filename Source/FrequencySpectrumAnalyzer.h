#pragma once
#include <JuceHeader.h>
namespace Neopolitan
{
class FrequencySpectrumAnalyzer
{
public:
   static constexpr auto fftOrder  = 11;            // [1]
   static constexpr auto fftSize   = 1 << fftOrder; // [2]
   static constexpr auto scopeSize = 512;           // [3]

   FrequencySpectrumAnalyzer()
   : forwardFFT(fftOrder)
   , window(fftSize, juce::dsp::WindowingFunction<float>::hann)
   {}

   ~FrequencySpectrumAnalyzer() = default;

   juce::dsp::WindowingFunction<float>& getWindow() { return window; }
   juce::dsp::FFT&                      getForwardFFT() { return forwardFFT; }

   void                                 pushNextSampleIntoFifo(float sample);

   float*                               getScopeData() { return scopeData; }

   float*                               getFftData() { return fftData; }

   int                                  getScopeSize() const { return scopeSize; }

   bool&                                getNextFFTBlockReady() { return nextFFTBlockReady; }

private:
   juce::dsp::FFT                      forwardFFT; // [4]
   juce::dsp::WindowingFunction<float> window;
   // [5]

   float fifo[fftSize];             // [6]
   float fftData[2 * fftSize];      // [7]
   int   fifoIndex         = 0;     // [8]
   bool  nextFFTBlockReady = false; // [9]
   float scopeData[scopeSize];
};
}