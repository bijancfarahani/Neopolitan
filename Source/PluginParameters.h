#pragma once

#include <JuceHeader.h>
//##include "magic"
//#inclu
#include "magic_enum.hpp"
#include <variant>

namespace Neopolitan
{
namespace PluginParams
{
   using APVTS            = juce::AudioProcessorValueTreeState;
   using RangedAudioParam = juce::RangedAudioParameter;
   using UniqueRAP        = std::unique_ptr<RangedAudioParam>;
   using UniqueRAPVector  = std::vector<UniqueRAP>;
   using APP              = juce::AudioProcessorParameter;
   using APF              = juce::AudioParameterFloat;
   using RangeF           = juce::NormalisableRange<float>;


   enum class PID
   {
      GainWet,
      Frequency,
      Vanilla_Mix,
      Strawberry_Mix,
      Chocolate_Mix,
      NumParams
   };
   static constexpr int NumParams = static_cast<int>(PID::NumParams);

   enum class Unit
   {
      Db,
      Hz,
      NumUnits
   };

   inline juce::String toName(PID pID)
   {
      return juce::String(magic_enum::enum_name(pID).data());
   }


   inline juce::String toID(const juce::String& name)
   {
      return name.toLowerCase().removeCharacters(" ");
   }

   inline juce::String toID(PID pID)
   {
      return toID(toName(pID));
   }

   inline juce::String toString(Unit unit)
   {
      switch (unit)
      {
      case Unit::Db:
         return "dB";
      case Unit::Hz:
         return "hz";
      default:
         return "Unknown";
      }
   }

   namespace range
   {
      template <typename ValueType>
      inline std::variant<RangeF> biased(ValueType start, ValueType end, ValueType bias) noexcept
      {
         // https://www.desmos.com/calculator/ps8q8gftcr
         const auto a  = bias * .5f + .5f;
         const auto a2 = 2.f * a;
         const auto aM = 1.f - a;

         const auto r  = end - start;
         const auto aR = r * a;
         if (bias != 0.f)
            return {
               start, end, [a2, aM, aR](ValueType min, ValueType, ValueType x) {
						const auto denom = aM - x + a2 * x;
						if (denom == 0.f)
							return min;
						return min + aR * x / denom; }, [a2, aM, aR](ValueType min, ValueType, ValueType x) {
						const auto denom = a2 * min + aR - a2 * x - min + x;
						if (denom == 0.f)
							return 0.f;
						auto val = aM * (x - min) / denom;
						return val > 1.f ? 1.f : val; }, [](ValueType min, ValueType max, ValueType x) { return x < min ? min : x > max ? max
                                                                                                                                                                                                                            : x; }
            };
         else
            return { start, end };
      }

      inline RangeF biased(float start, float end, float bias) noexcept
      {
         // https://www.desmos.com/calculator/ps8q8gftcr
         const auto a  = bias * .5f + .5f;
         const auto a2 = 2.f * a;
         const auto aM = 1.f - a;

         const auto r  = end - start;
         const auto aR = r * a;
         if (bias != 0.f)
            return {
               start, end, [a2, aM, aR](float min, float, float x) {
						const auto denom = aM - x + a2 * x;
						if (denom == 0.f)
							return min;
						return min + aR * x / denom; }, [a2, aM, aR](float min, float, float x) {
						const auto denom = a2 * min + aR - a2 * x - min + x;
						if (denom == 0.f)
							return 0.f;
						auto val = aM * (x - min) / denom;
						return val > 1.f ? 1.f : val; }, [](float min, float max, float x) { return x < min ? min : x > max ? max
                                                                                                                                                                                        : x; }
            };
         else
            return { start, end };
      }

      inline RangeF stepped(float start, float end, float steps = 1.f) noexcept
      {
         return { start, end, steps };
      }

      inline RangeF toggle() noexcept
      {
         return stepped(0.f, 1.f);
      }

      inline RangeF linear(float start, float end) noexcept
      {
         const auto range = end - start;

         return {
            start,
            end,
            [range](float min, float, float normalized) {
               return min + normalized * range;
            },
            [inv = 1.f / range](float min, float, float denormalized) {
               return (denormalized - min) * inv;
            },
            [](float min, float max, float x) {
               return juce::jlimit(min, max, x);
            }
         };
      }

      inline RangeF withCentre(float start, float end, float centre) noexcept
      {
         const auto r = end - start;
         const auto v = (centre - start) / r;

         return biased(start, end, 2.f * v - 1.f);
      }
   }

   using ValToStr = std::function<juce::String(float, int)>;
   using StrToVal = std::function<float(const juce::String&)>;

   namespace valToStr
   {
      inline ValToStr db()
      {
         return [](float val, int) {
            return juce::String(val, 2) + " dB";
         };
      }

      inline ValToStr hz()
      {
         return [](float val, int) {
            if (val < 100.f)
               return juce::String(val, 2) + " hz";
            else if (val < 1000.f)
               return juce::String(val, 1) + " hz";
            else if (val >= 1000.f)
            {
               auto k = val / 1000.f;
               return juce::String(k, 1) + " khz";
            }
            return juce::String();
         };
      }
   }

   namespace strToVal
   {
      inline StrToVal db()
      {
         return [](const juce::String& str) {
            return str.removeCharacters(toString(Unit::Db)).getFloatValue();
         };
      }

      inline StrToVal hz()
      {
         return [](const juce::String& str) {
            auto s = str.removeCharacters(toString(Unit::Hz));
            if (s.endsWith("k"))
            {
               s = s.dropLastCharacters(1);
               return s.getFloatValue() * 1000.f;
            }
            return s.getFloatValue();
         };
      }
   }

   inline void createParam(UniqueRAPVector& vec, PID pID, const RangeF& range, float defaultVal, const Unit unit)
   {
      ValToStr valToStrFunc;
      StrToVal strToValFunc;

      const auto name = toName(pID);
      const auto id   = toID(name);

      switch (unit)
      {
      case Unit::Db:
         valToStrFunc = valToStr::db();
         strToValFunc = strToVal::db();
         break;
      case Unit::Hz:
         valToStrFunc = valToStr::hz();
         strToValFunc = strToVal::hz();
         break;
      }

      vec.emplace_back(std::make_unique<APF>(
         id,
         name,
         range,
         defaultVal,
         toString(unit),
         APP::Category::genericParameter,
         valToStrFunc,
         strToValFunc));
   }




   // Factory of sorts for all the 'knobs and switches' and whatever
   // other types of controls we expose for interaction (both with
   // the user and other software such as a DAW).
   inline APVTS::ParameterLayout createParameterLayout()
   {
      UniqueRAPVector params;

      createParam(params, PID::GainWet, range::linear(-12.f, 12.f), 0.f, Unit::Db);

      createParam(params, PID::Vanilla_Mix, range::linear(-100.f, 0.f), -18.f, Unit::Db);
      createParam(params, PID::Chocolate_Mix, range::linear(-12.f, 12.f), 0.f, Unit::Db);
      createParam(params, PID::Strawberry_Mix, range::linear(-12.f, 12.f), 0.f, Unit::Db);

      createParam(params, PID::Frequency, range::withCentre(20.f, 20000.f, 1000.f), 1000.f, Unit::Hz);

      return { params.begin(), params.end() };
   }
}
}