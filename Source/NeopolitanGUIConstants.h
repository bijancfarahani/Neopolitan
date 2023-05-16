#pragma once

#include <cmath>

namespace Neopolitan
{
namespace GUI
{
   constexpr auto BACKGROUND_COLOUR_RED   = 152;
   constexpr auto BACKGROUND_COLOUR_GREEN = 184;
   constexpr auto BACKGROUND_COLOUR_BLUE  = 174;

   // Use the golden ratio for the window proportions.
   constexpr auto GOLDEN_RATIO          = 1.618;
   constexpr auto DEFAULT_WINDOW_HEIGHT = 720;
   const auto     DEFAULT_WINDOW_WIDTH =
      static_cast<int>(std::ceil(DEFAULT_WINDOW_HEIGHT * GOLDEN_RATIO));

   constexpr auto HEADER_HEIGHT = 36;
}
}