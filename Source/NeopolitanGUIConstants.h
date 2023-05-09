#pragma once

namespace Neopolitan
{
namespace GUI
{
   constexpr auto BACKGROUND_COLOUR_RED   = 152;
   constexpr auto BACKGROUND_COLOUR_GREEN = 184;
   constexpr auto BACKGROUND_COLOUR_BLUE  = 174;

   // Use the golden ratio for the window proportions.
   constexpr auto DEFAULT_WINDOW_HEIGHT = 720;
   constexpr auto DEFAULT_WINDOW_WIDTH  = DEFAULT_WINDOW_HEIGHT * 1.618;

   constexpr auto HEADER_HEIGHT = 36;
}
}