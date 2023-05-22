#include "FrequencySpectrumDisplay.h"

namespace Neopolitan
{

FrequencySpectrumDisplay::FrequencySpectrumDisplay(FrequencySpectrumAnalyzer& _freqSpectrumAnalyzer)
: _freqSpectrumAnalyzer(_freqSpectrumAnalyzer)
{
   startTimerHz(30);
}

void FrequencySpectrumDisplay::paint(juce::Graphics& g)
{
   g.fillAll(juce::Colours::black);

   g.setOpacity(1.0f);
   g.setColour(juce::Colours::white);
   _drawFrame(g);
}

void FrequencySpectrumDisplay::timerCallback()
{
   if (_freqSpectrumAnalyzer.getNextFFTBlockReady())
   {
      _drawNextFrameOfSpectrum();
      _freqSpectrumAnalyzer.getNextFFTBlockReady() = false;
      repaint();
   }
}

void FrequencySpectrumDisplay::_drawFrame(juce::Graphics& g)
{
   for (int i = 1; i < _freqSpectrumAnalyzer.getScopeSize(); ++i)
   {
      auto width  = getLocalBounds().getWidth();
      auto height = getLocalBounds().getHeight();
      g.drawLine(
            {static_cast<float>(
                   juce::jmap(i - 1, 0, _freqSpectrumAnalyzer.getScopeSize() - 1, 0, width)),
             juce::jmap(
                   _freqSpectrumAnalyzer.getScopeData()[i - 1],
                   0.0f,
                   1.0f,
                   static_cast<float>(height),
                   0.0f),
             static_cast<float>(
                   juce::jmap(i, 0, _freqSpectrumAnalyzer.getScopeSize() - 1, 0, width)),
             juce::jmap(
                   _freqSpectrumAnalyzer.getScopeData()[i],
                   0.0f,
                   1.0f,
                   static_cast<float>(height),
                   0.0f)});
   }
}

void FrequencySpectrumDisplay::_drawNextFrameOfSpectrum()
{
   // first apply a windowing function to our data
   _freqSpectrumAnalyzer.getWindow().multiplyWithWindowingTable(
         _freqSpectrumAnalyzer.getFftData(), _freqSpectrumAnalyzer.fftSize); // [1]

   // then render our FFT data..
   _freqSpectrumAnalyzer.getForwardFFT().performFrequencyOnlyForwardTransform(
         _freqSpectrumAnalyzer.getFftData()); // [2]

   auto mindB = -100.0f;
   auto maxdB = 0.0f;

   for (int i = 0; i < _freqSpectrumAnalyzer.getScopeSize(); ++i) // [3]
   {
      auto skewedProportionX =
            1.0f
            - std::exp(
                  std::log(
                        1.0f
                        - static_cast<float>(i)
                                / static_cast<float>(_freqSpectrumAnalyzer.getScopeSize()))
                  * 0.2f);
      auto fftDataIndex = juce::jlimit(
            0,
            _freqSpectrumAnalyzer.fftSize / 2,
            (int) (skewedProportionX * static_cast<float>(_freqSpectrumAnalyzer.fftSize * 0.5f)));
      auto level = juce::jmap(
            juce::jlimit(
                  mindB,
                  maxdB,
                  juce::Decibels::gainToDecibels(_freqSpectrumAnalyzer.getFftData()[fftDataIndex])
                        - juce::Decibels::gainToDecibels(
                              static_cast<float>(_freqSpectrumAnalyzer.fftSize))),
            mindB,
            maxdB,
            0.0f,
            1.0f);

      _freqSpectrumAnalyzer.getScopeData()[i] = level; // [4]
   }
}

}