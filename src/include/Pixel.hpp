#pragma once

#include "Vector.hpp"
#include "Color.hpp"

#include <iostream>

namespace ic {
    struct Pixel {
        Pixel(unsigned int X=0, unsigned int Y=0, unsigned char R=0, unsigned char G=0, unsigned char B=0) :
            pos{X, Y}, color{R, G, B}
        {
        }

        Pixel(Vector &v, Color &c) :
            pos{v}, color{c}
        {
        }

        ~Pixel() = default;

        Vector pos;
        Color color;
    };
}
std::ostream& operator<<(std::ostream& os, const ic::Pixel& pixel);