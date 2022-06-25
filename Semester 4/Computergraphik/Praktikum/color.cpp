//
// Created by phue on 4/24/22.
//

#include "color.h"

#include <algorithm>

color::RgbColor::RgbColor(float red, float green, float blue)
    :red(red), green(green), blue(blue) {}

color::RgbColor::operator CmyColor() const {
    float cyan = 1 - red;
    float magenta = 1 - green;
    float yellow = 1 - blue;

    return color::CmyColor(cyan, magenta, yellow);
}

color::RgbColor::operator HsvColor() const {
    float max = std::max(std::max(red, green), blue);
    float min = std::min(std::min(red, green), blue);

    float value = max;

    float hue = 0;
    if (max != min) {
        if (max == red) {
            hue = 60 * (0 + (green - blue) / (max - min));
        }
        else if (max == green) {
            hue = 60 * (2 + (blue - red) / (max - min));
        }
        else if (max == blue) {
            hue = 60 * (4 + (red - green) / (max - min));
        }

        if (hue < 0){
            hue += 360;
        }
    }

    float saturation = 0;
    if (value != 0) {
        saturation = (max - min) / max;
    }

    return color::HsvColor(hue, saturation, value);
}

color::CmyColor::CmyColor(float cyan, float magenta, float yellow)
    :cyan(cyan), magenta(magenta), yellow(yellow) {}

color::CmyColor::operator RgbColor() const {
    float red = 1 - cyan;
    float green = 1 - magenta;
    float blue = 1 - yellow;

    return color::RgbColor(red, green, blue);
}

color::HsvColor::HsvColor(float hue, float saturation, float value)
    :hue(hue), saturation(saturation), value(value) {}

color::HsvColor::operator RgbColor() const {
    int h = (hue / 60);
    float f = hue / 60 - h;

    float p  = value * (1 - saturation);
    float q = value * (1 - saturation * f);
    float t = value * (1 - saturation * (1 - f));

    float red = 0;
    float green = 0;
    float blue = 0;

    if (h == 0 || h == 6) {
        red = value;
        green = t;
        blue = p;
    } else if (h == 1) {
        red = q;
        green = value;
        blue = p;
    } else if (h == 2) {
        red = p;
        green = value;
        blue = t;
    } else if (h == 3) {
        red = p;
        green = q;
        blue = value;
    } else if (h == 4) {
        red = t;
        green = p;
        blue = value;
    } else if (h == 5) {
        red = value;
        green = p;
        blue = q;
    }

    return color::RgbColor(red, green, blue);
}

color::HsvColor::operator CmyColor() const {
    RgbColor rgb = static_cast<RgbColor>(*this);
    return static_cast<CmyColor>(rgb);
}
