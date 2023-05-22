#pragma once

#include "NeopolitanUtilities.h"
#include "magic_enum.hpp"
#include <JuceHeader.h>

namespace Neopolitan
{
namespace PluginParameters
{
   constexpr int NEOPOLITAN_PLUGIN_PARAMETER_VERSION = 1;

   // Add all the controls for our plugin here.
   enum class PID
   {
      Vanilla_Mix,
      Strawberry_Mix,
      Chocolate_Mix
   };
   constexpr std::size_t NumParams = magic_enum::enum_count<PID>();

   enum class Unit
   {
      Db,
      Hz
   };

   inline juce::String getParameterID(PID pID)
   {
      return Utilities::getEnumString(pID).toLowerCase().removeCharacters(" ");
   }

   // JUCE allows optional functions to parse text into a value.
   // This is because some plugins allow users to type in a value.
   // Ex) "5" could be 5dB or 5hz.
   using ValToStr = std::function<juce::String(float, int)>;
   using StrToVal = std::function<float(const juce::String&)>;

   namespace valToStr
   {
      inline ValToStr db()
      {
         return [](float val, int) { return juce::String(val, 2) + " dB"; };
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
            return str.removeCharacters(Utilities::getEnumString(Unit::Db)).getFloatValue();
         };
      }

      inline StrToVal hz()
      {
         return [](const juce::String& str) {
            auto s = str.removeCharacters(Utilities::getEnumString(Unit::Hz));
            if (s.endsWith("k"))
            {
               s = s.dropLastCharacters(1);
               return s.getFloatValue() * 1000.f;
            }
            return s.getFloatValue();
         };
      }
   }

   inline void createParam(
         std::vector<std::unique_ptr<juce::RangedAudioParameter>>& vec,
         PID                                                       pID,
         const juce::NormalisableRange<float>&                     range,
         float                                                     defaultVal,
         const Unit                                                unit)
   {
      ValToStr   valToStrFunc;
      StrToVal   strToValFunc;

      const auto name = Utilities::getEnumString(pID);
      const auto id   = getParameterID(pID);

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

      vec.emplace_back(std::make_unique<juce::AudioParameterFloat>(
            juce::ParameterID {id, NEOPOLITAN_PLUGIN_PARAMETER_VERSION},
            name,
            range,
            defaultVal,
            Utilities::getEnumString(unit),
            juce::AudioProcessorParameter::Category::genericParameter,
            valToStrFunc,
            strToValFunc));
   }

   // Factory of sorts for all the 'knobs and switches' and whatever
   // other types of controls we expose for interaction (both with
   // the user and other software such as a DAW).
   inline juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
   {
      std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

      createParam(params, PID::Vanilla_Mix, Utilities::Ranges::linear(-12.f, 12.f), 0.f, Unit::Db);
      createParam(
            params, PID::Chocolate_Mix, Utilities::Ranges::linear(-12.f, 12.f), 0.f, Unit::Db);
      createParam(
            params, PID::Strawberry_Mix, Utilities::Ranges::linear(-12.f, 12.f), 0.f, Unit::Db);

      return {params.begin(), params.end()};
   }
}
}