
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
#define MAKEHSL(hsl) HslColor((hsl[0] * 0.002777), (hsl[1] * 0.01), (hsl[2] * 0.005))

#define DEFAULT_COLOR COLOR_BLACK

