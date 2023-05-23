#pragma once
#include "magic_enum.hpp"
#include <JuceHeader.h>

namespace Neopolitan
{
enum class Unit
{
   Db,
   Hz
};
namespace NeoUtils
{
   template <typename E>
   concept EnumType = std::is_enum_v<E>;

   // Wrapper functions around magic_enum.
   template <EnumType Enum>
   // TODO: Can we return juce::StringRef instead?
   [[nodiscard]] juce::String getEnumString(Enum e)
   {
      return juce::String(magic_enum::enum_name(e).data());
   }

   // TODO: We can use concepts to generalize these to floating point (std::is_floating_point)
   // or possibily to integers as well (so std::is_arithmetic).  Try making an integer-ranged knob
   // and see how the GUI behaves.
   namespace Ranges
   {
      inline juce::NormalisableRange<float> biased(float start, float end, float bias) noexcept
      {
         // https://www.desmos.com/calculator/ps8q8gftcr
         const auto a  = bias * .5f + .5f;
         const auto a2 = 2.f * a;
         const auto aM = 1.f - a;

         const auto r  = end - start;
         const auto aR = r * a;
         if (bias != 0.f)
            return {
                  start,
                  end,
                  [a2, aM, aR](float min, float, float x) {
                     const auto denom = aM - x + a2 * x;
                     if (denom == 0.f)
                        return min;
                     return min + aR * x / denom;
                  },
                  [a2, aM, aR](float min, float, float x) {
                     const auto denom = a2 * min + aR - a2 * x - min + x;
                     if (denom == 0.f)
                        return 0.f;
                     auto val = aM * (x - min) / denom;
                     return val > 1.f ? 1.f : val;
                  },
                  [](float min, float max, float x) { return x < min ? min
                                                           : x > max ? max
                                                                     : x; }};
         else
            return {start, end};
      }

      inline juce::NormalisableRange<float>
            stepped(float start, float end, float steps = 1.f) noexcept
      {
         return {start, end, steps};
      }

      inline juce::NormalisableRange<float> toggle() noexcept { return stepped(0.f, 1.f); }

      inline juce::NormalisableRange<float> linear(float start, float end) noexcept
      {
         const auto range = end - start;

         return {
               start,
               end,
               [range](float min, float, float normalized) { return min + normalized * range; },
               [inv = 1.f / range](float min, float, float denormalized) {
                  return (denormalized - min) * inv;
               },
               [](float min, float max, float x) { return juce::jlimit(min, max, x); }};
      }

      inline juce::NormalisableRange<float>
            withCentre(float start, float end, float centre) noexcept
      {
         const auto r = end - start;
         const auto v = (centre - start) / r;

         return biased(start, end, 2.f * v - 1.f);
      }
   }
}
}