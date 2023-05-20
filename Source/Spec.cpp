#include "Spec.h"

namespace Neopolitan
{
void Spec::pushNextSampleIntoFifo(float sample)
{
   // if the fifo contains enough data, set a flag to say
   // that the next frame should now be rendered..
   if (fifoIndex == fftSize)  // [11]
   {
      if (!nextFFTBlockReady) // [12]
      {
         juce::zeromem(fftData, sizeof(fftData));
         memcpy(fftData, fifo, sizeof(fifo));
         nextFFTBlockReady = true;
      }

      fifoIndex = 0;
   }

   fifo[fifoIndex] = sample * 1000; // [12]
   fifoIndex++;
}
}