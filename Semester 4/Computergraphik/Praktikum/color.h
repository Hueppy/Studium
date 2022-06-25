//
// Created by phue on 4/24/22.
//

#ifndef BLATT01_COLOR_H
#define BLATT01_COLOR_H

#include <cstdint>

namespace color {
    struct CmyColor;
    struct HsvColor;

    struct RgbColor {
        RgbColor(float red, float green, float blue);

        explicit operator CmyColor() const;
        explicit operator HsvColor() const;

        float red, green, blue;
    };

    struct CmyColor {
        CmyColor(float cyan, float magenta, float yellow);

        explicit operator RgbColor() const;

        float cyan, magenta, yellow;
    };

    struct HsvColor {
        HsvColor(float hue, float saturation, float value);

        explicit operator RgbColor() const;
        explicit operator CmyColor() const;

        float hue, saturation, value;
    };
}

#endif //BLATT01_COLOR_H
