#pragma once

namespace Neopolitan
{

constexpr unsigned Num_Flavors = 3;
enum FlavorCode : unsigned
{
   Vanilla,
   Strawberry,
   Chocolate
};

constexpr auto Negative_Infinity_dB = -100.0f;

}