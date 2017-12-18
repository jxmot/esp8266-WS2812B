
#pragma once

#include <NeoPixelBus.h>

enum ColorSatLevel
{
    colorSat_none = -1,
    colorSat_min  = 0,
    colorSat_0    = colorSat_min,
    colorSat_25   = 64,
    colorSat_50   = 128,
    colorSat_75   = 192,
    colorSat_100  = 255,
    colorSat_max  = colorSat_100  
};

#define COLOR_BLACK RgbColor(colorSat_0, colorSat_0, colorSat_0)

#define MAKERGB(rgb) RgbColor(rgb[0], rgb[1], rgb[2])

#define DEFAULT_COLOR COLOR_BLACK

